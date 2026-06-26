#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>

#define INF INT_MAX

// ========================================================
// 1. MENU CODE (Data Structure: Vector/Array)
// ========================================================
struct FoodItem {
    int id;
    std::string name;
    double price;
};

class Menu {
private:
    std::vector<FoodItem> items;

public:
    Menu() {
        items = {
            {1, "Paneer Butter Masala", 250.0},
            {2, "Butter Naan", 50.0},
            {3, "Veg Biryani", 200.0},
            {4, "Masala Dosa", 120.0},
            {5, "Cold Coffee", 90.0}
        };
    }

    void displayMenu() {
        std::cout << "\n========== 📜 MENU ========== \n";
        for (const auto& item : items) {
            std::cout << item.id << ". " << item.name << " - Rs." << item.price << "\n";
        }
        std::cout << "=============================\n";
    }

    FoodItem getItem(int id) {
        for (const auto& item : items) {
            if (item.id == id) return item;
        }
        return {-1, "", 0.0}; 
    }
};

// ========================================================
// 2. MAP & ROUTING CODE (Data Structure: Graph + Dijkstra)
// ========================================================
class DeliveryMap {
private:
    int numVertices = 5; // 0: Restaurant, 1: Sector A, 2: Sector B, 3: Sector C, 4: Sector D
    std::vector<std::vector<int>> graph;

public:
    DeliveryMap() {
        // Distance matrix representing paths between different Sectors
        graph = {
            {0, 5, 10, INF, INF},
            {5, 0, 3, 11, INF},
            {10, 3, 0, 2, 8},
            {INF, 11, 2, 0, 6},
            {INF, INF, 8, 6, 0}
        };
    }

    void displayLocations() {
        std::cout << "\n📍 Available Delivery Locations:\n";
        std::cout << "1. Sector A\n2. Sector B\n3. Sector C\n4. Sector D\n";
    }

    // Shortest Path Logic using Dijkstra's Algorithm
    int calculateDeliveryTime(int destination) {
        std::vector<int> dist(numVertices, INF);
        std::vector<bool> visited(numVertices, false);

        dist[0] = 0; 

        for (int count = 0; count < numVertices - 1; count++) {
            int u = -1;
            for (int v = 0; v < numVertices; v++) {
                if (!visited[v] && (u == -1 || dist[v] < dist[u]))
                    u = v;
            }

            if (u == -1 || dist[u] == INF) break;
            visited[u] = true;

            for (int v = 0; v < numVertices; v++) {
                if (graph[u][v] != INF && dist[u] + graph[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph[u][v];
                }
            }
        }
        return dist[destination];
    }
};

// ========================================================
// 3. ORDER MANAGEMENT CODE (Data Structure: Queue - FIFO)
// ========================================================
struct Order {
    int orderId;
    std::string customerName;
    FoodItem item;
    int deliveryLocation; 
};

// ========================================================
// MAIN DRIVER CONTROL
// ========================================================
int main() {
    Menu menu;
    DeliveryMap deliveryMap;
    std::queue<Order> orderQueue;
    int orderCounter = 101;
    int choice;

    do {
        std::cout << "\n--- 🛵 SMART FOOD DELIVERY SYSTEM --- \n";
        std::cout << "1. View Menu & Place Order\n";
        std::cout << "2. View Pending Orders (Queue)\n";
        std::cout << "3. Process / Deliver Next Order\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                Order newOrder;
                newOrder.orderId = orderCounter++;
                
                std::cout << "\nEnter your name: ";
                std::cin.ignore();
                std::getline(std::cin, newOrder.customerName);

                menu.displayMenu();
                std::cout << "Enter Item ID to order: ";
                int itemId;
                std::cin >> itemId;
                
                newOrder.item = menu.getItem(itemId);
                if (newOrder.item.id == -1) {
                    std::cout << "❌ Invalid Item ID! Order cancelled. 🚫\n";
                    orderCounter--;
                    break;
                }

                deliveryMap.displayLocations();
                std::cout << "Select your delivery location sector (1-4): ";
                std::cin >> newOrder.deliveryLocation;
                
                if (newOrder.deliveryLocation < 1 || newOrder.deliveryLocation > 4) {
                    std::cout << "❌ Invalid location! Order cancelled. 🚫\n";
                    orderCounter--;
                    break;
                }

                orderQueue.push(newOrder);
                std::cout << "✅ Order placed successfully! Your Order ID is: " << newOrder.orderId << "\n";
                break;
            }
            case 2: {
                if (orderQueue.empty()) {
                    std::cout << "\n📭 No pending orders right now!\n";
                } else {
                    std::cout << "\n📋 Pending Orders Queue:\n";
                    std::queue<Order> tempQueue = orderQueue; 
                    while (!tempQueue.empty()) {
                        Order current = tempQueue.front();
                        std::cout << "ID: " << current.orderId << " | Name: " << current.customerName 
                                  << " | Item: " << current.item.name << "\n";
                        tempQueue.pop();
                    }
                }
                break;
            }
            case 3: {
                if (orderQueue.empty()) {
                    std::cout << "\n🎉 All orders delivered! Nothing to process. 🚀\n";
                } else {
                    Order currentOrder = orderQueue.front();
                    orderQueue.pop();

                    std::cout << "\n🔄 Processing Order #" << currentOrder.orderId << " for " << currentOrder.customerName << "...\n";
                    std::cout << "📦 Food prepared: " << currentOrder.item.name << "\n";
                    
                    int travelTime = deliveryMap.calculateDeliveryTime(currentOrder.deliveryLocation); 
                    
                    std::cout << "🛵 Valet is on the way to Sector " << char('A' + currentOrder.deliveryLocation - 1) << "...\n";
                    std::cout << "⏱️ Estimated delivery time (Shortest Route via Dijkstra): " << travelTime << " minutes.\n";
                    std::cout << "💵 Total amount collected: Rs. " << currentOrder.item.price << "\n";
                    std::cout << "✅ Order successfully delivered! 🎉\n";
                }
                break;
            }
            case 4:
                std::cout << "\nExiting... Thank you for using Smart Food Delivery! 👋✨\n";
                break;
            default:
                std::cout << "❌ Invalid choice! Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
