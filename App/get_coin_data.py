import sys
from binance.client import Client
from datetime import datetime, timedelta

def get_price_change(client, symbol, interval, days_ago):
    """
    Fetches historical price data and calculates price change.
    """
    # Calculate the timestamp for the desired past date
    end_time = datetime.now() - timedelta(days=days_ago)
    # Fetch candlestick for the day 'days_ago'
    candles = client.get_historical_klines(symbol, interval, start_str=str(end_time), end_str=str(end_time + timedelta(days=1)), limit=1)
    if not candles:
        raise ValueError("No historical data returned.")
    open_price = float(candles[0][1])
    current_price = float(client.get_symbol_ticker(symbol=symbol)['price'])
    price_change = current_price - open_price
    price_change_percent = (price_change / open_price) * 100
    return current_price, price_change, price_change_percent

def main(symbol, duration):
    api_key = 'your_api_key'
    api_secret = 'your_api_secret'
    client = Client(api_key, api_secret)

    if duration == '24h':
        days_ago = 1
    elif duration == '7d':
        days_ago = 7
    elif duration == '1m':
        days_ago = 30
    else:
        raise ValueError("Invalid duration. Choose '24h', '7d', or '1m'.")

    current_price, price_change, price_change_percent = get_price_change(client, symbol, '1d', days_ago)
    print(f"{symbol} Current Price: ${current_price:.2f}, {duration} Change: ${price_change:.2f} ({price_change_percent:.2f}%)")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python get_coin_data.py <symbol> <duration>")
        sys.exit(1)

    symbol = sys.argv[1].upper()  # Ensure the symbol is in uppercase
    duration = sys.argv[2].lower()  # Ensure the duration is in lowercase
    main(symbol, duration)
