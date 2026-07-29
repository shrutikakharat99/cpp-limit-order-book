# Market Microstructure

=========== Introduction ===========

Financial markets exist to facilitate the exchange of financial instruments between buyers and sellers. While this process may appear simple from a user's perspective, modern electronic exchanges execute millions of transactions every second while ensuring fairness, determinism, and reliability.

When an investor clicks the Buy or Sell button on a trading platform such as Zerodha, Groww, Robinhood, or Interactive Brokers, the order does not immediately become a trade. Instead, it enters a complex system responsible for validating, storing, matching, and executing orders.

Understanding how this system works is fundamental to quantitative trading, market microstructure, and low-latency software engineering.

This chapter introduces the core concepts behind modern electronic markets and lays the foundation for the implementation of our own Limit Order Book and Matching Engine.

=========== Why Market Microstructure Matters ===========

A common misconception is that stock exchanges simply connect buyers and sellers.

In reality, an exchange is a highly optimized distributed software system responsible for:

- Receiving orders from market participants
- Maintaining an accurate view of active buy and sell orders
- Matching compatible orders
- Executing trades according to predefined rules
- Publishing market data to all participants

Every financial trade begins with an order and ends with a trade. Everything in between is the responsibility of the exchange.

For quantitative developers and low-latency engineers, understanding this process is essential because trading strategies ultimately interact with these exchange mechanisms.

=========== Evolution of Financial Markets ===========

Historically, trades were executed through open outcry, where traders physically gathered on an exchange floor and negotiated prices.


Buyer
   ¦
   ?
Exchange Floor
   ?
   ¦
Seller

Although effective for its time, this approach suffered from several limitations:

- Limited scalability
- Human error
- Slow execution
- Lack of transparency
- Geographic constraints

Today, nearly all major exchanges operate electronically.

Buyer
    ¦
    ?
Broker
    ¦
    ?
Electronic Exchange
    ¦
    ?
Matching Engine
    ¦
    ?
Trade

The trading floor has effectively been replaced by software.

=========== Participants in an Electronic Market ===========

Several participants interact to complete a trade.

# Investor

The individual or institution wishing to buy or sell a financial instrument.

Examples include:

- Retail investors
- Mutual funds
- Hedge funds
- Banks
- Proprietary trading firms

# Broker

Investors cannot directly submit orders to most exchanges.

Instead, they place orders through brokers, who forward these orders to the exchange after performing regulatory and risk checks.

Examples include:

- Zerodha
- Groww
- Interactive Brokers
- Charles Schwab

# Exchange

The exchange acts as a neutral marketplace.

Its responsibilities include:

- Receiving orders
- Maintaining the order book
- Matching buyers and sellers
- Executing trades
- Publishing market data

Importantly, the exchange does not decide whether a trade is profitable. Its responsibility is simply to execute trades according to predefined rules.

=========== Order Lifecycle ===========

Every trade begins with an order.

The simplified lifecycle of an order is shown below.

Trader
   ¦
Broker
   ¦
Exchange
   ¦
Order Validation
   ¦
Matching Engine
   ¦
   +--------------+
   ¦              ¦
Matched?         No Match
   ¦              ¦
Trade        Limit Order Book

If the incoming order can immediately trade against an existing order, a trade is executed.

Otherwise, the order remains in the Limit Order Book until a compatible order arrives or the order is cancelled.

=========== The Two Core Components ===========

Modern electronic exchanges revolve around two fundamental components.

1. Limit Order Book (LOB)

The Limit Order Book stores all active buy and sell orders waiting to be executed.

It is essentially the exchange's memory.

The order book maintains:

- Buy orders (Bids)
- Sell orders (Asks)
- Price levels
- Order priority

The order book does not execute trades.

Its primary responsibility is storing and organizing orders efficiently.

2. Matching Engine

The Matching Engine is the decision-making component.

Whenever a new order arrives, it determines whether the order can trade against existing orders.

If a compatible order exists:

- Generate one or more trades
- Update remaining quantities
- Update the order book

Otherwise:

- Insert the order into the Limit Order Book

Unlike the Order Book, the Matching Engine contains business logic rather than storage logic.

=========== Why Deterministic Matching Matters ===========

Imagine three investors submit identical orders.

```
09:00:01   Alice
09:00:02   Bob
09:00:03   Charlie
```

When another trader arrives, who should receive the trade first?

If the exchange behaved randomly, markets would be considered unfair.

Instead, exchanges follow deterministic matching rules.

The most common rule is Price-Time Priority, where:

1. Better prices receive higher priority.
2. Among equal prices, earlier orders execute first.

This guarantees fairness and predictable behaviour.

Price-Time Priority will become the central algorithm implemented in this project.

=========== Engineering Perspective ===========

From a software engineering perspective, an electronic exchange is fundamentally a high-performance event processing system.

Each incoming order represents an event that must be processed with:

- Low latency
- High throughput
- Deterministic behaviour
- Fault tolerance
- Efficient memory usage

Although financial markets introduce domain-specific terminology, the underlying engineering challenges resemble those found in other distributed systems:

- Data structure design
- Algorithm optimization
- Memory management
- Concurrency
- Performance profiling

Understanding both the financial concepts and the engineering principles is essential when building trading infrastructure.

=========== Connection to Our Implementation ===========

Throughout this project we will gradually implement simplified versions of the components found in real electronic exchanges.

The implementation roadmap is:

Incoming Order
        ¦
        ?
Matching Engine
        ¦
        +-------------+
        ¦             ¦
Trade?              No Trade
        ¦             ¦
        ?             ?
Generate Trade   Limit Order Book

Over the next chapters we will progressively design and implement:

- Order representation
- Trade representation
- Limit Order Book
- Matching Engine
- Order cancellation
- Order modification
- Unit testing
- Benchmarking
- Low-latency optimizations

The goal is not merely to build a working system, but to understand the reasoning behind every architectural and implementation decision.

=========== Summary ===========

Modern financial exchanges are sophisticated software systems designed to efficiently connect buyers and sellers while maintaining fairness, determinism, and high performance.

The two primary components of such systems are the Limit Order Book, which stores active orders, and the Matching Engine, which determines how and when trades occur.

This chapter provides the conceptual foundation for the remainder of the project.

In the next chapter, we will study the different types of orders that participants can submit to an exchange and examine how each order type influences the behaviour of the Matching Engine.