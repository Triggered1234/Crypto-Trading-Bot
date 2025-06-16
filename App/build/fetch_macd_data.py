import sys
import argparse
import pandas as pd
from binance.client import Client
from binance.enums import KLINE_INTERVAL_1MINUTE
import pandas_ta as ta

def fetch_macd(api_key, api_secret, coin_id):
    try:
        client = Client(api_key, api_secret)
        klines = client.get_historical_klines(coin_id, KLINE_INTERVAL_1MINUTE, "1 day ago UTC")

        if not klines or len(klines) < 35:
            print("0 0")  # fallback values
            sys.stdout.flush()
            return

        df = pd.DataFrame(klines, columns=[
            'timestamp', 'open', 'high', 'low', 'close', 'volume',
            'close_time', 'quote_asset_volume', 'number_of_trades',
            'taker_buy_base_asset_volume', 'taker_buy_quote_asset_volume', 'ignore'
        ])
        df['close'] = df['close'].astype(float)

        df.ta.macd(append=True)

        if 'MACD_12_26_9' not in df.columns or 'MACDs_12_26_9' not in df.columns:
            print("0 0")
            sys.stdout.flush()
            return

        macd_line = df['MACD_12_26_9'].iloc[-1]
        signal_line = df['MACDs_12_26_9'].iloc[-1]

        if pd.isna(macd_line) or pd.isna(signal_line):
            print("0 0")
        else:
            print(f"{macd_line} {signal_line}")

        sys.stdout.flush()

    except Exception as e:
        print(f"Error: {str(e)}")
        sys.stdout.flush()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Fetch MACD from Binance")
    parser.add_argument('api_key', type=str, help='API key')
    parser.add_argument('api_secret', type=str, help='API secret')
    parser.add_argument('coin_id', type=str, help='Trading pair symbol (e.g., BTCUSDT)')

    args = parser.parse_args()
    fetch_macd(args.api_key, args.api_secret, args.coin_id)
