#include "Expedia.hpp"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QCryptographicHash>
#include <QSqlError>


QString hashPassword(const QString &password)
{
    return QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
}

User *GlobalState::currentUser = nullptr;
Itinerary *GlobalState::currentItinerary = nullptr;

void GlobalState::setCurrentUser(User *user)
{
    if (currentUser)
        delete currentUser;
    currentUser = user;
}

User *GlobalState::getCurrentUser()
{
    return currentUser;
}

void GlobalState::clearCurrentUser()
{
    if (currentUser)
    {
        delete currentUser;
        currentUser = nullptr;
    }
}

void GlobalState::setCurrentItinerary(Itinerary *itinerary)
{
    if (currentItinerary)
        delete currentItinerary;
    currentItinerary = itinerary;
}

Itinerary *GlobalState::getCurrentItinerary()
{
    return currentItinerary;
}

bool InitializeDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("expedia.db");
    if (!db.open())
    {
        qDebug() << "Error opening database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "username TEXT PRIMARY KEY,"
               "password TEXT,"
               "fullName TEXT,"
               "role TEXT)");
    query.exec("CREATE TABLE IF NOT EXISTS flights ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "airline TEXT,"
               "from_city TEXT,"
               "to_city TEXT,"
               "date_time_from TEXT,"
               "date_time_to TEXT,"
               "price REAL)");
    query.exec("CREATE TABLE IF NOT EXISTS hotels ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "hotel_chain TEXT,"
               "city TEXT,"
               "room_type TEXT,"
               "date_from TEXT,"
               "date_to TEXT,"
               "price_per_night REAL)");
    query.exec("CREATE TABLE IF NOT EXISTS bookings ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "username TEXT,"
               "flight_id INTEGER,"
               "hotel_id INTEGER,"
               "total_cost REAL,"
               "status TEXT)");
    db.close();
    return true;
}

void InitializeUsers()
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("INSERT OR IGNORE INTO users (username, password, fullName, role) VALUES (:username, :password, :fullName, :role)");
        query.bindValue(":username", "user");
        query.bindValue(":password", hashPassword("password"));
        query.bindValue(":fullName", "Test User");
        query.bindValue(":role", "customer");
        query.exec();

        query.prepare("INSERT OR IGNORE INTO users (username, password, fullName, role) VALUES (:username, :password, :fullName, :role)");
        query.bindValue(":username", "admin");
        query.bindValue(":password", hashPassword("admin"));
        query.bindValue(":fullName", "Admin User");
        query.bindValue(":role", "manager");
        query.exec();
        db.close();
    }
}

std::vector<std::unique_ptr<AirCanadaFlight>> AirCanadaAPI::GetFlights(const std::string &from, const std::string &to,
                                                                       const std::string &fromDate, const std::string &toDate,
                                                                       int adults, int children)
{
    std::vector<std::unique_ptr<AirCanadaFlight>> flights;
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("SELECT id, price, date_time_from, date_time_to FROM flights WHERE from_city = :from AND to_city = :to AND airline = 'AirCanada'");
        query.bindValue(":from", QString::fromStdString(from));
        query.bindValue(":to", QString::fromStdString(to));
        if (query.exec())
        {
            while (query.next())
            {
                auto flight = std::make_unique<AirCanadaFlight>();
                flight->id = query.value("id").toInt();
                flight->price = query.value("price").toDouble();
                flight->date_time_from = query.value("date_time_from").toString().toStdString();
                flight->date_time_to = query.value("date_time_to").toString().toStdString();
                flights.push_back(std::move(flight));
            }
        }
        db.close();
    }
    return flights;
}

bool AirCanadaAPI::ReserveFlight(AirCanadaFlight *flight)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO bookings (username, flight_id, total_cost, status) VALUES (:username, :flight_id, :total_cost, 'Paid')");
        query.bindValue(":username", QString::fromStdString(GlobalState::getCurrentUser()->username));
        query.bindValue(":flight_id", flight->id);
        query.bindValue(":total_cost", flight->price);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

bool AirCanadaAPI::CancelFlight(AirCanadaFlight *flight)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("UPDATE bookings SET status = 'Cancelled' WHERE flight_id = :flight_id");
        query.bindValue(":flight_id", flight->id);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

std::vector<std::unique_ptr<TurkishFlight>> TurkishAirlinesAPI::GetFlights(const std::string &from, const std::string &to,
                                                                           const std::string &fromDate, const std::string &toDate,
                                                                           int adults, int children, int infants)
{
    std::vector<std::unique_ptr<TurkishFlight>> flights;
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("SELECT id, price, date_time_from, date_time_to FROM flights WHERE from_city = :from AND to_city = :to AND airline = 'TurkishAirlines'");
        query.bindValue(":from", QString::fromStdString(from));
        query.bindValue(":to", QString::fromStdString(to));
        if (query.exec())
        {
            while (query.next())
            {
                auto flight = std::make_unique<TurkishFlight>();
                flight->id = query.value("id").toInt();
                flight->price = query.value("price").toDouble();
                flight->date_time_from = query.value("date_time_from").toString().toStdString();
                flight->date_time_to = query.value("date_time_to").toString().toStdString();
                flights.push_back(std::move(flight));
            }
        }
        db.close();
    }
    return flights;
}

bool TurkishAirlinesAPI::ReserveFlight(TurkishFlight *flight)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO bookings (username, flight_id, total_cost, status) VALUES (:username, :flight_id, :total_cost, 'Paid')");
        query.bindValue(":username", QString::fromStdString(GlobalState::getCurrentUser()->username));
        query.bindValue(":flight_id", flight->id);
        query.bindValue(":total_cost", flight->price);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

bool TurkishAirlinesAPI::CancelFlight(TurkishFlight *flight)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("UPDATE bookings SET status = 'Cancelled' WHERE flight_id = :flight_id");
        query.bindValue(":flight_id", flight->id);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

std::vector<std::unique_ptr<HiltonRoom>> HotelAPI::GetHiltonRooms(const std::string &city, const std::string &fromDate,
                                                                  const std::string &toDate, int adults, int children)
{
    std::vector<std::unique_ptr<HiltonRoom>> rooms;
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("SELECT id, room_type, price_per_night, date_from, date_to FROM hotels WHERE city = :city AND hotel_chain = 'Hilton'");
        query.bindValue(":city", QString::fromStdString(city));
        if (query.exec())
        {
            while (query.next())
            {
                auto room = std::make_unique<HiltonRoom>();
                room->id = query.value("id").toInt();
                room->room_type = query.value("room_type").toString().toStdString();
                room->price_per_night = query.value("price_per_night").toDouble();
                room->date_from = query.value("date_from").toString().toStdString();
                room->date_to = query.value("date_to").toString().toStdString();
                rooms.push_back(std::move(room));
            }
        }
        db.close();
    }
    return rooms;
}

std::vector<std::unique_ptr<MarriottRoom>> HotelAPI::GetMarriottRooms(const std::string &city, const std::string &fromDate,
                                                                      const std::string &toDate, int adults, int children)
{
    std::vector<std::unique_ptr<MarriottRoom>> rooms;
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("SELECT id, room_type, price_per_night, date_from, date_to FROM hotels WHERE city = :city AND hotel_chain = 'Marriott'");
        query.bindValue(":city", QString::fromStdString(city));
        if (query.exec())
        {
            while (query.next())
            {
                auto room = std::make_unique<MarriottRoom>();
                room->id = query.value("id").toInt();
                room->room_type = query.value("room_type").toString().toStdString();
                room->price_per_night = query.value("price_per_night").toDouble();
                room->date_from = query.value("date_from").toString().toStdString();
                room->date_to = query.value("date_to").toString().toStdString();
                rooms.push_back(std::move(room));
            }
        }
        db.close();
    }
    return rooms;
}

bool HotelAPI::ReserveRoom(HiltonRoom *room)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO bookings (username, hotel_id, total_cost, status) VALUES (:username, :hotel_id, :total_cost, 'Paid')");
        query.bindValue(":username", QString::fromStdString(GlobalState::getCurrentUser()->username));
        query.bindValue(":hotel_id", room->id);
        query.bindValue(":total_cost", room->price_per_night);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

bool HotelAPI::ReserveRoom(MarriottRoom *room)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO bookings (username, hotel_id, total_cost, status) VALUES (:username, :hotel_id, :total_cost, 'Paid')");
        query.bindValue(":username", QString::fromStdString(GlobalState::getCurrentUser()->username));
        query.bindValue(":hotel_id", room->id);
        query.bindValue(":total_cost", room->price_per_night);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

bool HotelAPI::CancelRoom(HiltonRoom *room)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("UPDATE bookings SET status = 'Cancelled' WHERE hotel_id = :hotel_id");
        query.bindValue(":hotel_id", room->id);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

bool HotelAPI::CancelRoom(MarriottRoom *room)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("UPDATE bookings SET status = 'Cancelled' WHERE hotel_id = :hotel_id");
        query.bindValue(":hotel_id", room->id);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

bool StripeAPI::WithdrawMoney(const std::string &user, const std::string &card, double amount)
{
    QSqlDatabase db = QSqlDatabase::database();
    if (db.open())
    {
        QSqlQuery query(db);
        query.prepare("INSERT INTO bookings (username, total_cost, status) VALUES (:username, :total_cost, 'Paid')");
        query.bindValue(":username", QString::fromStdString(user));
        query.bindValue(":total_cost", amount);
        bool success = query.exec();
        db.close();
        return success;
    }
    return false;
}

double Itinerary::getTotalCost() const
{
    double total = 0.0;
    for (const auto &f : flights)
        total += f->price;
    for (const auto &f : turkish_flights)
        total += f->price;
    for (const auto &h : hotels)
        total += h->price_per_night * h->nights;
    for (const auto &h : marriott_rooms)
        total += h->price_per_night * h->nights;
    return total;
}
