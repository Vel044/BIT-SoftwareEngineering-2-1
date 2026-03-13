#include <iostream>
#include <list>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
struct Order
{
    int order_id;
    int stock_code;
    double price;
    int quantity;
    char buy_sell;

    Order(int id, int code, double p, int q, char bs)
        : order_id(id), stock_code(code), price(p), quantity(q), buy_sell(bs) {}
};

class StockExchange
{
public:
    void PlaceOrder(int stock_code, double price, int quantity, char buy_sell)
    {
        int order_id = GetNextOrderId();
        std::cout << "orderid: " << std::setw(4) << std::setfill('0') << order_id << std::endl;
        Order new_order(order_id, stock_code, price, quantity, buy_sell);
        MatchOrders(new_order);

        if (new_order.quantity > 0)
        {
            if (buy_sell == 'b')
                buy_orders.push_back(new_order);
            else
                sell_orders.push_back(new_order);
        }
    }

    void QueryOrders(int stock_code)
    {
        std::cout << "buy orders:" << std::endl;
        PrintOrders(buy_orders, stock_code);
        std::cout << "sell orders:" << std::endl;
        PrintOrders(sell_orders, stock_code);
    }

    void CancelOrder(int order_id)
    {
        auto it = FindOrder(order_id);
        if (it != buy_orders.end() && it != sell_orders.end())
        {
            std::cout << "deleted order:";
            PrintOrder(*it);
            if (it == buy_orders.end())
                buy_orders.erase(it);
            else
                sell_orders.erase(it);
        }
        else
        {
            std::cout << "not found" << std::endl;
        }
    }

private:
    int GetNextOrderId()
    {
        return ++order_counter;
    }

    void PrintOrder(const Order &order)
    {
        std::cout << "orderid: " << std::setw(4) << std::setfill('0') << order.order_id;
        std::cout << ", stockid:" << std::setw(4) << std::setfill('0') << order.stock_code;
        std::cout << ", price: " << std::setw(6) << std::setfill(' ') << std::fixed << std::setprecision(1) << order.price;
        std::cout << ", quantity: " << std::setw(4) << std::setfill(' ') << order.quantity;
        std::cout << ", b/s: " << order.buy_sell << std::endl;
    }

    void PrintOrders(const std::list<Order> &orders, int stock_code)
    {
        // 创建临时向量以便排序
        std::vector<Order> sortedOrders;

        // 将符合条件的订单复制到临时向量
        for (const auto &order : orders)
        {
            if (order.stock_code == stock_code)
                sortedOrders.push_back(order);
        }

        // 对买单按价格从高到低排序
        std::sort(sortedOrders.begin(), sortedOrders.end(), [](const Order &a, const Order &b)
                  {
                      if (a.buy_sell == 'b' && b.buy_sell == 'b') // 对买单按价格从高到低排序
                          return a.price > b.price;
                      else if (a.buy_sell == 's' && b.buy_sell == 's') // 对卖单按价格从低到高排序
                          return a.price < b.price;
                      return a.order_id < b.order_id; // 处理同一价格下的订单ID排序
                  });

        // 输出排序后的订单
        for (const auto &order : sortedOrders)
        {
            PrintOrder(order);
        }
    }

    /*
        void MatchOrders(Order &new_order)
        {
            if (new_order.buy_sell == 'b')
            {
                // 处理新的买单（buy order）
                for (auto it = sell_orders.begin(); it != sell_orders.end();)
                {
                    if (new_order.stock_code == it->stock_code && new_order.price >= it->price)
                    {
                        int deal_quantity = std::min(new_order.quantity, it->quantity);
                        double deal_price = (new_order.price + it->price) / 2;
                        new_order.quantity -= deal_quantity;
                        it->quantity -= deal_quantity;

                        std::cout << "deal--price: " << std::setw(5) << std::setfill(' ') << std::fixed << std::setprecision(1) << deal_price;
                        std::cout << "  quantity: " << std::setw(3) << deal_quantity;
                        std::cout << "  buyorder:" << std::setw(4) << std::setfill('0') << new_order.order_id;
                        std::cout << "  sellorder:" << std::setw(4) << std::setfill('0') << it->order_id << std::endl;

                        if (it->quantity == 0)
                            it = sell_orders.erase(it);
                        if (new_order.quantity == 0)
                            break;
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
            else if (new_order.buy_sell == 's')
            {
                // 处理新的卖单（sell order）
                for (auto it = buy_orders.begin(); it != buy_orders.end();)
                {
                    if (new_order.stock_code == it->stock_code && new_order.price <= it->price)
                    {
                        int deal_quantity = std::min(new_order.quantity, it->quantity);
                        double deal_price = (new_order.price + it->price) / 2;
                        new_order.quantity -= deal_quantity;
                        it->quantity -= deal_quantity;

                        std::cout << "deal--price: " << std::setw(6) << std::setfill(' ') << std::fixed << std::setprecision(1) << deal_price;
                        std::cout << " quantity: " << std::setw(4) << std::setfill('0') << deal_quantity;
                        std::cout << " sellorder:" << std::setw(4) << std::setfill('0') << new_order.order_id;
                        std::cout << " buyorder:" << std::setw(4) << std::setfill('0') << it->order_id << std::endl;

                        if (it->quantity == 0)
                            it = buy_orders.erase(it);
                        if (new_order.quantity == 0)
                            break;
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
        }*/
    void MatchOrders(Order &new_order)
    {
        if (new_order.buy_sell == 'b')
        {
            // 对卖单列表按照价格从低到高排序
            sell_orders.sort([](const Order &a, const Order &b)
                             { return a.price < b.price; });

            // 处理新的买单（buy order）
            for (auto it = sell_orders.begin(); it != sell_orders.end();)
            {
                if (new_order.stock_code == it->stock_code && new_order.price >= it->price)
                {
                    int deal_quantity = std::min(new_order.quantity, it->quantity);
                    double deal_price = (new_order.price + it->price) / 2;
                    new_order.quantity -= deal_quantity;
                    it->quantity -= deal_quantity;

                    std::cout << "deal--price: " << std::setw(5) << std::setfill(' ') << std::fixed << std::setprecision(1) << deal_price;
                    std::cout << "  quantity:" << std::setw(4) << std::setfill(' ') << deal_quantity;
                    std::cout << "  buyorder:" << std::setw(4) << std::setfill('0') << new_order.order_id;
                    std::cout << "  sellorder:" << std::setw(4) << std::setfill('0') << it->order_id << std::endl;

                    if (it->quantity == 0)
                        it = sell_orders.erase(it);
                    if (new_order.quantity == 0)
                        break;
                }
                else
                {
                    ++it;
                }
            }
        }
        else if (new_order.buy_sell == 's')
        {
            // 对买单列表按照价格从高到低排序
            buy_orders.sort([](const Order &a, const Order &b)
                            { return a.price > b.price; });

            // 处理新的卖单（sell order）
            for (auto it = buy_orders.begin(); it != buy_orders.end();)
            {
                if (new_order.stock_code == it->stock_code && new_order.price <= it->price)
                {
                    int deal_quantity = std::min(new_order.quantity, it->quantity);
                    double deal_price = (new_order.price + it->price) / 2;
                    new_order.quantity -= deal_quantity;
                    it->quantity -= deal_quantity;

                    std::cout << "deal--price: " << std::setw(5) << std::setfill(' ') << std::fixed << std::setprecision(1) << deal_price;
                    std::cout << "  quantity:" << std::setw(4) <<  std::setfill(' ') << deal_quantity;
                    std::cout << "  sellorder:" << std::setw(4) << std::setfill('0') << new_order.order_id;
                    std::cout << "  buyorder:" << std::setw(4) << std::setfill('0') << it->order_id << std::endl;

                    if (it->quantity == 0)
                        it = buy_orders.erase(it);
                    if (new_order.quantity == 0)
                        break;
                }
                else
                {
                    ++it;
                }
            }
        }
    }

    std::list<Order>::iterator FindOrder(int order_id)
    {
        for (auto it = buy_orders.begin(); it != buy_orders.end(); ++it)
        {
            if (it->order_id == order_id)
            {
                return it;
            }
        }
        for (auto it = sell_orders.begin(); it != sell_orders.end(); ++it)
        {
            if (it->order_id == order_id)
            {
                return it;
            }
        }
        return buy_orders.end();
    }

    std::list<Order> buy_orders;  // 买队列
    std::list<Order> sell_orders; // 卖队列
    int order_counter = 0;        // id
};

int main()
{
    StockExchange exchange;
    int command;

    while (true)
    {
        std::cin >> command;
        if (command == 0)
        {
            break;
        }
        if (command == 1)
        {
            int stock_code, quantity;
            double price;
            char buy_sell;
            std::cin >> stock_code >> price >> quantity >> buy_sell;
            exchange.PlaceOrder(stock_code, price, quantity, buy_sell);
        }
        else if (command == 2)
        {
            int stock_code;
            std::cin >> stock_code;
            exchange.QueryOrders(stock_code);
        }
        else if (command == 3)
        {
            int order_id;
            std::cin >> order_id;
            exchange.CancelOrder(order_id);
        }
    }
    return 0;
}
