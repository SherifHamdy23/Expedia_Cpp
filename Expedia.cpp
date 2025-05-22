#include "Expedia.hpp"

// Initialize static members
User* GlobalState::currentUser = nullptr;
Itinerary* GlobalState::currentItinerary = nullptr;
std::map<std::string, User*> GlobalState::Users;

// AirCanadaAPI implementations
std::vector<AirCanadaFlight*> AirCanadaAPI::GetFlights(const std::string& from, const std::string& to,
                                                        const std::string& fromDate, const std::string& toDate,
                                                        int adults, int children) {
    std::vector<AirCanadaFlight*> flights;
    AirCanadaFlight* f1 = new AirCanadaFlight{200.0, "25-01-22", "10-02-22"};
    AirCanadaFlight* f2 = new AirCanadaFlight{250.0, "29-01-22", "10-02-22"};
    AirCanadaFlight* f3 = new AirCanadaFlight{200.0, "25-01-22", "10-02-22"};
    AirCanadaFlight* f4 = new AirCanadaFlight{250.0, "29-01-22", "10-02-22"};
    AirCanadaFlight* f5 = new AirCanadaFlight{200.0, "25-01-22", "10-02-22"};
    AirCanadaFlight* f6 = new AirCanadaFlight{250.0, "29-01-22", "10-02-22"};
    flights.push_back(f1);
    flights.push_back(f2);
    flights.push_back(f3);
    flights.push_back(f4);
    flights.push_back(f5);
    flights.push_back(f6);
    return flights;
}

bool AirCanadaAPI::ReserveFlight(AirCanadaFlight* flight) { return true; }
bool AirCanadaAPI::CancelFlight(AirCanadaFlight* flight) { return true; }

// TurkishAirlinesAPI implementations
std::vector<TurkishFlight*> TurkishAirlinesAPI::GetFlights(const std::string& from, const std::string& to,
                                                            const std::string& fromDate, const std::string& toDate,
                                                            int adults, int children, int infants) {
    std::vector<TurkishFlight*> flights;
    TurkishFlight* f1 = new TurkishFlight{300.0, "10-01-22", "10-02-22"};
    TurkishFlight* f2 = new TurkishFlight{320.0, "12-01-22", "10-02-22"};
    flights.push_back(f1);
    flights.push_back(f2);
    return flights;
}

bool TurkishAirlinesAPI::ReserveFlight(TurkishFlight* flight) { return true; }
bool TurkishAirlinesAPI::CancelFlight(TurkishFlight* flight) { return true; }

// HotelAPI implementations
std::vector<HiltonRoom*> HotelAPI::GetHiltonRooms(const std::string& city, const std::string& fromDate,
                                                   const std::string& toDate, int adults, int children) {
    std::vector<HiltonRoom*> rooms;
    HiltonRoom* r1 = new HiltonRoom{"Interior View", 200.0, "29-01-22", "10-02-22"};
    HiltonRoom* r2 = new HiltonRoom{"City View", 300.0, "29-01-22", "10-02-22"};
    HiltonRoom* r3 = new HiltonRoom{"Deluxe View", 500.0, "29-01-22", "10-02-22"};
    rooms.push_back(r1);
    rooms.push_back(r2);
    rooms.push_back(r3);
    return rooms;
}

std::vector<MarriottRoom*> HotelAPI::GetMarriottRooms(const std::string& city, const std::string& fromDate,
                                                       const std::string& toDate, int adults, int children) {
    std::vector<MarriottRoom*> rooms;
    MarriottRoom* r1 = new MarriottRoom{"City View", 320.0, "29-01-22", "10-02-22"};
    MarriottRoom* r2 = new MarriottRoom{"Interior View", 220.0, "29-01-22", "10-02-22"};
    MarriottRoom* r3 = new MarriottRoom{"Private View", 600.0, "29-01-22", "10-02-22"};
    rooms.push_back(r1);
    rooms.push_back(r2);
    rooms.push_back(r3);
    return rooms;
}

bool HotelAPI::ReserveRoom(HiltonRoom* room) { return true; }
bool HotelAPI::ReserveRoom(MarriottRoom* room) { return true; }
bool HotelAPI::CancelRoom(HiltonRoom* room) { return true; }
bool HotelAPI::CancelRoom(MarriottRoom* room) { return true; }

// StripeAPI implementation
bool StripeAPI::WithdrawMoney(const std::string& user, const std::string& card, double amount) { return true; }

// Itinerary implementation
Itinerary::Itinerary() : flights(), hotels() {}

double Itinerary::getTotalCost() const {
    double total = 0.0;
    for (const auto* f : flights) total += f->price;
    for (const auto* h : hotels) total += h->pricePerNight * h->nights;
    return total;
}

// User implementation
User::User(const std::string& uname, const std::string& pwd, const std::string& fname, const std::string& role)
    : username(uname), password(pwd), fullName(fname), role(role), itineraries() {}

// GlobalState implementations
User* GlobalState::getCurrentUser() { return currentUser; }
void GlobalState::setCurrentUser(User* value) { currentUser = value; }
Itinerary* GlobalState::getCurrentItinerary() { return currentItinerary; }
void GlobalState::setCurrentItinerary(Itinerary* value) { currentItinerary = value; }

// Initialize default user
void InitializeUsers() {
    GlobalState::Users["shefoo"] = new User("shefoo", "password", "Sherif Hamdy Mohamed", "customer");
    GlobalState::Users["admin"] = new User("admin", "admin", "Dr/ Tayseer Fahmy", "manager");
}
