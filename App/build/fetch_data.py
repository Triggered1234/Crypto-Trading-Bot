import sys
import pandas as pd
from binance.client import Client
from binance.enums import KLINE_INTERVAL_1MINUTE
import pandas_ta as ta

def fetch_data(api_key, api_secret, coin_id):
    # Initialize Binance client
    client = Client(api_key, api_secret)

    # Fetch historical data (1-minute intervals for intraday trading)
    klines = client.get_historical_klines(coin_id, KLINE_INTERVAL_1MINUTE, "1 day ago UTC")

    # Create a DataFrame from the klines data
    df = pd.DataFrame(klines, columns=[
        'timestamp', 'open', 'high', 'low', 'close', 'volume', 
        'close_time', 'quote_asset_volume', 'number_of_trades', 
        'taker_buy_base_asset_volume', 'taker_buy_quote_asset_volume', 'ignore'
    ])
    
    # Convert the close prices to float
    df['close'] = df['close'].astype(float)

    # Ensure the DataFrame has enough data
    if df.shape[0] < 35:  # 35 is the minimum for MACD (26 + 9)
        print("Not enough data to compute MACD and RSI")
        return

    # Calculate MACD and RSI using pandas-ta
    macd = ta.macd(df['close'])
    rsi = ta.rsi(df['close'])

    # Check if the indicators were calculated correctly
    if macd is None or rsi is None or macd.empty or rsi.empty:
        print("Error calculating indicators")
        return

    # Get the last values
    macd_red_line = macd['MACD_12_26_9'].iloc[-1]
    macd_blue_line = macd['MACDs_12_26_9'].iloc[-1]
    rsi_value = rsi.iloc[-1]

    # Print fetched values to stdout
    print(macd_red_line, macd_blue_line, rsi_value)

if __name__ == "__main__":
    # Accept coin ID from command-line arguments
    coin_id = sys.argv[1]
    
    # Fetch data
    fetch_data("S4DDhuhW2r7BU8klFngZaIx7OkUGRfEbx7ozR9oaBGZDtlU8H5X0faNRGtu98FF2", "dbTXtfL0odCNOf7mBltRikGawV0014yBypwaEAmzYQU86W5bXE7wwJvS7S7RkDTd", coin_id)
