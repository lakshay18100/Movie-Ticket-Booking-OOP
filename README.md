# 🎬 Movie Ticket Booking System (C++ OOP)

![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![OOP](https://img.shields.io/badge/Paradigm-Object--Oriented%20Programming-2EA44F?style=for-the-badge)
![Platform](https://img.shields.io/badge/Interface-CLI%20Console-lightgrey?style=for-the-badge)

> A sleek, console-based **Movie Ticket Booking System** engineered in C++ to demonstrate core **Object-Oriented Programming (OOP)** principles—Encapsulation, Inheritance, and Runtime Polymorphism—in a clean, real-world architecture.

---

## ✨ Key Features

* **🎥 Browse Movies & Showtimes:** View currently screening titles, genres, and available show slots at a glance.
* **💺 Interactive 5x5 Seat Matrix:** Visual seating layout (`[O]` Available, `[X]` Booked) with real-time boundary and double-booking validation.
* **🎟️ Multi-Tier Ticket Booking:** Choose between **Standard** (Rs. 250) and **IMAX 3D Experience** (Rs. 450, inclusive of surcharge & 3D glasses) with automated dynamic billing.
* **🔄 Instant Cancellation & Refunds:** Cancel active tickets via unique Booking IDs (`#1001`, `#1002`, etc.), automatically freeing the seat and calculating the exact refund.
* **📋 Live Booking Summary:** View all active reservations made during the session in formatted ticket stubs.

---

## 🧠 OOP Architecture & Concepts Used

| OOP Pillar | Implementation in Project |
| :--- | :--- |
| **🔒 Encapsulation** | The `Movie` class isolates its 5x5 seat matrix (`seats[5][5]`) and metadata as `private`. Seat states can only be altered via controlled public methods (`bookSeat()` and `cancelSeat()`). |
| **🧬 Inheritance** | `IMAXTicket` publicly inherits core attributes (`bookingId`, `movieTitle`, `showTime`, `seatLabel`, `basePrice`) from the base `Ticket` class, eliminating code duplication. |
| **⚡ Polymorphism** | Active bookings are stored in a `vector<Ticket*>`. Virtual functions (`calculatePrice()` and `displayTicket()`) are overridden in `IMAXTicket` to resolve pricing and receipt formatting dynamically at runtime. |
| **🧹 Memory Management** | Heap-allocated ticket objects (`new`) are cleanly deallocated (`delete`) upon ticket cancellation and program termination to prevent memory leaks. |

---

## 📂 Repository Structure

```text
Movie-Ticket-Booking-OOP/
├── main.cpp            # Complete C++ source code (Classes + CLI Controller)
├── sample_output.txt   # Recorded CLI walkthrough with sample bookings & cancellations
└── README.md           # Project documentation