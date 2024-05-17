import sys
from binance.client import Client
from binance.enums import KLINE_INTERVAL_1HOUR
from talib import MACD, RSI

def fetch_data(api_key, api_secret, coin_id):
    # Initialize Binance client
    client = Client(api_key, api_secret)

    # Fetch historical data (1-hour intervals for simplicity)
    klines = client.get_historical_klines(coin_id, KLINE_INTERVAL_1HOUR, "1 day ago UTC")

    # Extract close prices
    close_prices = [float(kline[4]) for kline in klines]

    # Calculate MACD and RSI
    macd, macd_signal, _ = MACD(close_prices)
    rsi = RSI(close_prices)

    # Get the last values
    macd_red_line = macd[-1]
    macd_blue_line = macd_signal[-1]
    rsi_value = rsi[-1]

    # Print fetched values to stdout
    print(macd_red_line, macd_blue_line, rsi_value)

if __name__ == "__main__":
    # Accept API key, API secret, and coin ID from command-line arguments
    # api_key = sys.argv[1]
    # api_secret = sys.argv[2]
    coin_id = sys.argv[1]
    
    # Fetch data
    fetch_data("S4DDhuhW2r7BU8klFngZaIx7OkUGRfEbx7ozR9oaBGZDtlU8H5X0faNRGtu98FF2", "dbTXtfL0odCNOf7mBltRikGawV0014yBypwaEAmzYQU86W5bXE7wwJvS7S7RkDTd", coin_id)