import argparse
from binance.client import Client
from binance.enums import SIDE_BUY, ORDER_TYPE_LIMIT, TIME_IN_FORCE_GTC
from binance.exceptions import BinanceAPIException, BinanceOrderException

def get_symbol_price(client, symbol):
    try:
        ticker = client.get_symbol_ticker(symbol=symbol)
        return float(ticker['price'])
    except BinanceAPIException as e:
        print(f"An error occurred while fetching the symbol price: {e}")
        return None

def place_order(client, symbol, quantity, price=None):
    try:
        if price is None:
            price = get_symbol_price(client, symbol)
            if price is None:
                print("Failed to retrieve the current price. Cannot place order.")
                return

            price += 1  # conform comportamentului anterior

        order = client.create_order(
            symbol=symbol,
            side=SIDE_BUY,
            type=ORDER_TYPE_LIMIT,
            timeInForce=TIME_IN_FORCE_GTC,
            quantity=quantity,
            price='{:.8f}'.format(price)
        )
        print("Order placed successfully:")
        print(order)
    except BinanceAPIException as e:
        print(f"An error occurred while placing the order: {e}")
    except BinanceOrderException as e:
        print(f"An order error occurred: {e}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Place a buy order on Binance testnet.')
    parser.add_argument('api_key', type=str, help='Binance API key')
    parser.add_argument('api_secret', type=str, help='Binance API secret')
    parser.add_argument('symbol', type=str, help='The trading pair symbol (e.g., BTCUSDT)')
    parser.add_argument('quantity', type=float, help='The quantity to buy')
    parser.add_argument('--price', type=float, help='The price at which to buy (optional, uses current price if not provided)')

    args = parser.parse_args()

    client = Client(args.api_key, args.api_secret, testnet=True)

    place_order(client, args.symbol, args.quantity, args.price)
