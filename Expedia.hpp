#ifndef EXPEDIA_HPP
#define EXPEDIA_HPP

#include <string>
#include <vector>
#include <map>

// Simulated API structures
struct AirCanadaFlight {
    double price;
    std::string date_time_from;
    std::string date_time_to;
};

struct TurkishFlight {
    double price;
    std::string date_time_from;
    std::string date_time_to;
};

struct HiltonRoom {
    std::string room_type;
    double price_per_night;
    std::string date_from;
    std::string date_to;
};

struct MarriottRoom {
    std::string room_type;
    double price_per_night;
    std::string date_from;
    std::string date_to;
};

// Simulated APIs
class AirCanadaAPI {
public:
    static std::vector<AirCanadaFlight*> GetFlights(const std::string& from, const std::string& to,
                                                     const std::string& fromDate, const std::string& toDate,
                                                     int adults, int children);
    static bool ReserveFlight(AirCanadaFlight* flight);
    static bool CancelFlight(AirCanadaFlight* flight);
};

class TurkishAirlinesAPI {
public:
    static std::vector<TurkishFlight*> GetFlights(const std::string& from, const std::string& to,
                                                   const std::string& fromDate, const std::string& toDate,
                                                   int adults, int children, int infants);
    static bool ReserveFlight(TurkishFlight* flight);
    static bool CancelFlight(TurkishFlight* flight);
};

class HotelAPI {
public:
    static std::vector<HiltonRoom*> GetHiltonRooms(const std::string& city, const std::string& fromDate,
                                                    const std::string& toDate, int adults, int children);
    static std::vector<MarriottRoom*> GetMarriottRooms(const std::string& city, const std::string& fromDate,
                                                        const std::string& toDate, int adults, int children);
    static bool ReserveRoom(HiltonRoom* room);
    static bool ReserveRoom(MarriottRoom* room);
    static bool CancelRoom(HiltonRoom* room);
    static bool CancelRoom(MarriottRoom* room);
};

class StripeAPI {
public:
    static bool WithdrawMoney(const std::string& user, const std::string& card, double amount);
};

// Data structures
struct Flight {
    std::string airline, from, to, departure, arrival;
    double price;
    int adults, children, infants;
};

struct Hotel {
    std::string name, city, country, roomType, from, to;
    double pricePerNight;
    int nights, adults, children;
};

struct Itinerary {
    std::vector<Flight*> flights;
    std::vector<Hotel*> hotels;
    Itinerary();
    double getTotalCost() const;
};

struct User {
    std::string username, password, fullName;
    std::vector<Itinerary*> itineraries;
    User(const std::string& uname, const std::string& pwd, const std::string& fname);
};

// Global state manager
class GlobalState {
public:
    static User* getCurrentUser();
    static void setCurrentUser(User* value);
    static Itinerary* getCurrentItinerary();
    static void setCurrentItinerary(Itinerary* value);
    static std::map<std::string, User*> Users;

private:
    static User* currentUser;
    static Itinerary* currentItinerary;
};

// Function to initialize default user
void InitializeUsers();

#endif // EXPEDIA_HPP
