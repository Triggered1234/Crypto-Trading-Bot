import argparse
from binance.client import Client
from binance.enums import SIDE_SELL, ORDER_TYPE_LIMIT

def place_order(client, symbol, side, quantity, price):
    try:
        order = client.create_order(
            symbol=symbol,
            side=side,
            type=ORDER_TYPE_LIMIT,
            timeInForce='GTC',
            quantity=quantity,
            price='{:.8f}'.format(price)
        )
        print("Order placed successfully:")
        print(order)
    except Exception as e:
        print("An error occurred while placing the order:")
        print(e)

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Place a sell order on Binance.')
    parser.add_argument('api_key', type=str, help='API key')
    parser.add_argument('api_secret', type=str, help='API secret')
    parser.add_argument('symbol', type=str, help='Trading pair symbol (e.g. BTCUSDT)')
    parser.add_argument('quantity', type=float, help='Quantity to sell')
    parser.add_argument('price', type=float, help='Price at which to sell')

    args = parser.parse_args()

    client = Client(args.api_key, args.api_secret)
    place_order(client, args.symbol, SIDE_SELL, args.quantity, args.price)
