#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// ==========================================
// 1. ENCAPSULATION: Movie & Seat Management
// ==========================================
class Movie {
private:
    string title;
    string genre;
    vector<string> showTimings;
    // 5x5 Seat Matrix: false = Available, true = Booked
    bool seats[5][5];

public:
    Movie(string t, string g, vector<string> times) 
        : title(t), genre(g), showTimings(times) {
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 5; j++) {
                seats[i][j] = false;
            }
        }
    }

    string getTitle() const { return title; }
    vector<string> getTimings() const { return showTimings; }

    void displayInfo() const {
        cout << "Movie: " << title << " (" << genre << ")\n   Timings: ";
        for (size_t i = 0; i < showTimings.size(); i++) {
            cout << "[" << i + 1 << "] " << showTimings[i] << "  ";
        }
        cout << "\n";
    }

    void displaySeats() const {
        cout << "\n--- Seat Layout for " << title << " ---\n";
        cout << "   1  2  3  4  5\n";
        for (int i = 0; i < 5; i++) {
            cout << char('A' + i) << " ";
            for (int j = 0; j < 5; j++) {
                cout << (seats[i][j] ? "[X]" : "[O]");
            }
            cout << "\n";
        }
        cout << "([O] = Available, [X] = Booked)\n";
    }

    bool bookSeat(int row, int col) {
        if (row < 0 || row >= 5 || col < 0 || col >= 5) {
            cout << "Invalid seat coordinates!\n";
            return false;
        }
        if (seats[row][col]) {
            cout << "Seat is already booked!\n";
            return false;
        }
        seats[row][col] = true;
        return true;
    }

    bool cancelSeat(int row, int col) {
        if (row < 0 || row >= 5 || col < 0 || col >= 5) {
            cout << "Invalid seat coordinates!\n";
            return false;
        }
        if (!seats[row][col]) {
            cout << "Seat is not currently booked!\n";
            return false;
        }
        seats[row][col] = false;
        return true;
    }
};

// ==========================================
// 2. INHERITANCE & POLYMORPHISM: Ticket Hierarchy
// ==========================================
class Ticket {
protected:
    int bookingId;
    string movieTitle;
    string showTime;
    string seatLabel;
    double basePrice;

public:
    Ticket(int id, string title, string time, string seat, double price)
        : bookingId(id), movieTitle(title), showTime(time), seatLabel(seat), basePrice(price) {}

    virtual ~Ticket() {}

    int getBookingId() const { return bookingId; }
    string getMovieTitle() const { return movieTitle; }
    string getSeatLabel() const { return seatLabel; }

    // Virtual function for Runtime Polymorphism
    virtual double calculatePrice() const {
        return basePrice; // Standard price
    }

    virtual void displayTicket() const {
        cout << "----------------------------------------\n";
        cout << "Booking ID : #" << bookingId << " [STANDARD]\n";
        cout << "Movie      : " << movieTitle << "\n";
        cout << "Show Time  : " << showTime << "\n";
        cout << "Seat       : " << seatLabel << "\n";
        cout << "Total Paid : Rs. " << fixed << setprecision(2) << calculatePrice() << "\n";
        cout << "----------------------------------------\n";
    }
};

// Derived Class demonstrating Inheritance
class IMAXTicket : public Ticket {
private:
    double imaxSurcharge;
    double glassesFee;

public:
    IMAXTicket(int id, string title, string time, string seat, double price)
        : Ticket(id, title, time, seat, price), imaxSurcharge(150.0), glassesFee(50.0) {}

    // Overriding calculatePrice() for Polymorphism
    double calculatePrice() const override {
        return basePrice + imaxSurcharge + glassesFee;
    }

    void displayTicket() const override {
        cout << "----------------------------------------\n";
        cout << "Booking ID : #" << bookingId << " [IMAX 3D EXPERIENCE]\n";
        cout << "Movie      : " << movieTitle << "\n";
        cout << "Show Time  : " << showTime << "\n";
        cout << "Seat       : " << seatLabel << "\n";
        cout << "Total Paid : Rs. " << fixed << setprecision(2) << calculatePrice() << "\n";
        cout << "----------------------------------------\n";
    }
};

// ==========================================
// 3. SYSTEM CONTROLLER & MAIN MENU
// ==========================================
int main() {
    // Initialize sample movies
    vector<Movie> movies = {
        Movie("Interstellar", "Sci-Fi", {"10:00 AM", "02:30 PM", "07:00 PM"}),
        Movie("Spider-Man: Beyond", "Action", {"11:15 AM", "04:00 PM", "09:15 PM"}),
        Movie("Kalki 2898 AD", "Sci-Fi/Mythology", {"01:00 PM", "06:30 PM", "10:00 PM"})
    };

    // Base class pointers vector to achieve Polymorphism
    vector<Ticket*> bookedTickets;
    int nextBookingId = 1001;
    int choice;

    while (true) {
        cout << "\n========================================\n";
        cout << "      MOVIE TICKET BOOKING SYSTEM       \n";
        cout << "========================================\n";
        cout << "1. Display Movies & Show Timings\n";
        cout << "2. Book a Ticket\n";
        cout << "3. Cancel a Ticket\n";
        cout << "4. View My Bookings\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            cout << "\n--- Now Showing ---\n";
            for (size_t i = 0; i < movies.size(); i++) {
                cout << i + 1 << ". ";
                movies[i].displayInfo();
            }
        } 
        else if (choice == 2) {
            int movieIdx, timeIdx, typeChoice, col;
            char rowChar;

            cout << "\nSelect Movie (1-" << movies.size() << "): ";
            cin >> movieIdx;
            if (movieIdx < 1 || movieIdx > (int)movies.size()) {
                cout << "Invalid movie selection!\n";
                continue;
            }
            Movie& selectedMovie = movies[movieIdx - 1];

            selectedMovie.displayInfo();
            cout << "Select Show Timing (1-" << selectedMovie.getTimings().size() << "): ";
            cin >> timeIdx;
            if (timeIdx < 1 || timeIdx > (int)selectedMovie.getTimings().size()) {
                cout << "Invalid timing selection!\n";
                continue;
            }
            string selectedTime = selectedMovie.getTimings()[timeIdx - 1];

            selectedMovie.displaySeats();
            cout << "Enter Row (A-E) and Column (1-5) (e.g., B 3): ";
            cin >> rowChar >> col;
            rowChar = toupper(rowChar);
            int row = rowChar - 'A';
            int colIdx = col - 1;

            if (selectedMovie.bookSeat(row, colIdx)) {
                cout << "Select Ticket Type (1. Standard [Rs. 250] | 2. IMAX 3D [Rs. 450]): ";
                cin >> typeChoice;

                string seatLabel = string(1, rowChar) + to_string(col);
                Ticket* newTicket = nullptr;

                if (typeChoice == 2) {
                    newTicket = new IMAXTicket(nextBookingId++, selectedMovie.getTitle(), selectedTime, seatLabel, 250.0);
                } else {
                    newTicket = new Ticket(nextBookingId++, selectedMovie.getTitle(), selectedTime, seatLabel, 250.0);
                }

                bookedTickets.push_back(newTicket);
                cout << "\nBooking Successful!\n";
                newTicket->displayTicket();
            }
        } 
        else if (choice == 3) {
            int cancelId;
            cout << "\nEnter Booking ID to cancel: ";
            cin >> cancelId;

            bool found = false;
            for (size_t i = 0; i < bookedTickets.size(); i++) {
                if (bookedTickets[i]->getBookingId() == cancelId) {
                    // Free the seat in the corresponding movie
                    string mTitle = bookedTickets[i]->getMovieTitle();
                    string sLabel = bookedTickets[i]->getSeatLabel();
                    int row = sLabel[0] - 'A';
                    int col = (sLabel[1] - '0') - 1;

                    for (auto& m : movies) {
                        if (m.getTitle() == mTitle) {
                            m.cancelSeat(row, col);
                            break;
                        }
                    }

                    cout << "Ticket #" << cancelId << " cancelled. Refund of Rs. " 
                         << bookedTickets[i]->calculatePrice() << " initiated.\n";

                    delete bookedTickets[i]; // Free allocated memory
                    bookedTickets.erase(bookedTickets.begin() + i);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Booking ID not found!\n";
            }
        } 
        else if (choice == 4) {
            if (bookedTickets.empty()) {
                cout << "\nNo active bookings found.\n";
            } else {
                cout << "\n--- Your Booked Tickets ---\n";
                for (const auto& ticket : bookedTickets) {
                    ticket->displayTicket(); // Polymorphic call
                }
            }
        } 
        else if (choice == 5) {
            // Clean up dynamically allocated memory before exiting
            for (auto& ticket : bookedTickets) {
                delete ticket;
            }
            cout << "Thank you for using the Movie Ticket Booking System!\n";
            break;
        } 
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}