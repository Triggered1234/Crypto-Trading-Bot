import os
import argparse
from binance.client import Client
from binance.enums import SIDE_SELL, ORDER_TYPE_LIMIT, TIME_IN_FORCE_GTC
from binance.exceptions import BinanceAPIException, BinanceOrderException

# Replace these with your actual testnet API keys or set them in your environment variables
api_key = os.getenv('BINANCE_TESTNET_API_KEY', 'pQN3vI2m0PlM6SbyeBh8EVvphFHhT8hxvSD3WwfknEmQm7mPRBdQGXofVcFXHT8u')
api_secret = os.getenv('BINANCE_TESTNET_API_SECRET', 'V4Am9EVSgP72lbeqeRvxIugwco3je1yVMXpYmuFsdQKyLSUXkGShk97R9IXmtMIu')

# Initialize the Binance client with the testnet URL
client = Client(api_key, api_secret, testnet=True)

def get_symbol_price(symbol):
    """
    Gets the current price of a trading pair symbol.

    :param symbol: The trading pair symbol (e.g., 'BTCUSDT')
    :return: The current price of the trading pair
    """
    try:
        ticker = client.get_symbol_ticker(symbol=symbol)
        return float(ticker['price'])
    except BinanceAPIException as e:
        print(f"An error occurred while fetching the symbol price: {e}")
        return None

def place_order(symbol, quantity, price=None):
    """
    Places an order on Binance testnet.

    :param symbol: The trading pair symbol (e.g., 'BTCUSDT')
    :param quantity: The amount to buy or sell
    :param price: The price at which to buy or sell (if None, use current market price)
    """
    try:
        if price is None:
            price = get_symbol_price(symbol) - 1
            if price is None:
                print("Failed to retrieve the current price. Cannot place order.")
                return

        order = client.create_order(
            symbol=symbol,
            side=SIDE_SELL,
            type=ORDER_TYPE_LIMIT,
            timeInForce=TIME_IN_FORCE_GTC,  # Good till cancelled
            quantity=quantity,
            price='{:.8f}'.format(price)  # format price to 8 decimal places
        )
        print("Order placed successfully:")
        print(order)
    except BinanceAPIException as e:
        print(f"An error occurred while placing the order: {e}")
    except BinanceOrderException as e:
        print(f"An order error occurred: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Place a buy order on Binance testnet.')
    parser.add_argument('symbol', type=str, help='The trading pair symbol (e.g., BTCUSDT)')
    parser.add_argument('quantity', type=float, help='The quantity to buy')
    parser.add_argument('--price', type=float, help='The price at which to buy (optional, uses current price if not provided)')

    args = parser.parse_args()

    place_order(args.symbol, args.quantity, args.price)
