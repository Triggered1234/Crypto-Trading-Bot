import os
from binance.client import Client
from binance.enums import SIDE_BUY, SIDE_SELL, ORDER_TYPE_LIMIT

# Get your API and secret key from environment variables or hardcode them (not recommended for security reasons)
api_key = os.getenv('BINANCE_API_KEY')  # replace with your actual API key if not using environment variables
api_secret = os.getenv('BINANCE_API_SECRET')  # replace with your actual secret key if not using environment variables

client = Client(api_key, api_secret)

def place_order(symbol, side, quantity, price):
    """
    Places an order on Binance.

    :param symbol: The trading pair symbol (e.g., 'BTCUSDT')
    :param side: 'BUY' or 'SELL'
    :param quantity: The amount to buy or sell
    :param price: The price at which to buy or sell
    """
    try:
        order = client.create_order(
            symbol=symbol,
            side=side,
            type=ORDER_TYPE_LIMIT,
            timeInForce='GTC',  # Good till cancelled
            quantity=quantity,
            price='{:.8f}'.format(price)  # format price to 8 decimal places
        )
        print("Order placed successfully:")
        print(order)
    except Exception as e:
        print("An error occurred while placing the order:")
        print(e)

if __name__ == "__main__":
    # Example usage:
    trading_pair = 'BTCUSDT'
    order_side = SIDE_SELL
    order_quantity = 0.001  # Adjust the quantity as needed
    order_price = 30000.00  # Adjust the price as needed

    place_order(trading_pair, order_side, order_quantity, order_price)
