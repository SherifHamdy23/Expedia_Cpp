#ifndef EXPEDIA_HPP
#define EXPEDIA_HPP

#include <QString>
#include <vector>
#include <memory>
bool InitializeDatabase();
void InitializeUsers();
struct User
{
    std::string username;
    std::string fullName;
    std::string role;
};

struct AirCanadaFlight
{
    int id;
    double price;
    std::string date_time_from;
    std::string date_time_to;
};

struct TurkishFlight
{
    int id;
    double price;
    std::string date_time_from;
    std::string date_time_to;
};

struct HiltonRoom
{
    int id;
    std::string room_type;
    double price_per_night;
    std::string date_from;
    std::string date_to;
    int nights = 1;
};

struct MarriottRoom
{
    int id;
    std::string room_type;
    double price_per_night;
    std::string date_from;
    std::string date_to;
    int nights = 1;
};

class Itinerary
{
public:
    std::vector<std::unique_ptr<AirCanadaFlight>> flights;
    std::vector<std::unique_ptr<TurkishFlight>> turkish_flights;
    std::vector<std::unique_ptr<HiltonRoom>> hotels;
    std::vector<std::unique_ptr<MarriottRoom>> marriott_rooms;
    double getTotalCost() const;
};

class GlobalState
{
public:
    static User *getCurrentUser();
    static void setCurrentUser(User *user);
    static void clearCurrentUser();
    static Itinerary *getCurrentItinerary();
    static void setCurrentItinerary(Itinerary *itinerary);

private:
    static User *currentUser;
    static Itinerary *currentItinerary;
};

class AirCanadaAPI
{
public:
    static std::vector<std::unique_ptr<AirCanadaFlight>> GetFlights(const std::string &from, const std::string &to,
                                                                    const std::string &fromDate, const std::string &toDate,
                                                                    int adults, int children);
    static bool ReserveFlight(AirCanadaFlight *flight);
    static bool CancelFlight(AirCanadaFlight *flight);
};

class TurkishAirlinesAPI
{
public:
    static std::vector<std::unique_ptr<TurkishFlight>> GetFlights(const std::string &from, const std::string &to,
                                                                  const std::string &fromDate, const std::string &toDate,
                                                                  int adults, int children, int infants);
    static bool ReserveFlight(TurkishFlight *flight);
    static bool CancelFlight(TurkishFlight *flight);
};

class HotelAPI
{
public:
    static std::vector<std::unique_ptr<HiltonRoom>> GetHiltonRooms(const std::string &city, const std::string &fromDate,
                                                                   const std::string &toDate, int adults, int children);
    static std::vector<std::unique_ptr<MarriottRoom>> GetMarriottRooms(const std::string &city, const std::string &fromDate,
                                                                       const std::string &toDate, int adults, int children);
    static bool ReserveRoom(HiltonRoom *room);
    static bool ReserveRoom(MarriottRoom *room);
    static bool CancelRoom(HiltonRoom *room);
    static bool CancelRoom(MarriottRoom *room);
};

class StripeAPI
{
public:
    static bool WithdrawMoney(const std::string &user, const std::string &card, double amount);
};

QString hashPassword(const QString &password);
bool InitializeDatabase();
void InitializeUsers();

#endif // EXPEDIA_HPP
