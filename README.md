# 🛵 Smart Food Delivery System (DSA Project)

A console-based, efficient food ordering and routing application built using **C++** and fundamental Data Structures and Algorithms. 

## 🚀 Key Features & DSA Implemented
* **Order Placement & Scheduling:** Implemented using a **Queue (FIFO)** structure to process incoming orders sequentially.
* **Menu Management:** Structured using dynamic **Vectors** for optimal storage and retrieval of active food items.
* **Smart Route Optimization:** Uses **Dijkstra's Algorithm** on an adjacency matrix-based **Graph** to calculate the quickest delivery path from the restaurant to various sectors.

## 📂 Project Structure
* `SmartFoodDelivery.cpp` - The core application file containing the implementation of the Menu, Order Queue, Map, and Dijkstra's routing engine.

## 💻 How to Run Locally
1. Clone the repository or download the `.cpp` file.
2. Open your terminal in the directory and compile using `g++`:
   ```bash
   g++ SmartFoodDelivery.cpp -o FoodDelivery
