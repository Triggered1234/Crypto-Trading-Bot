import sys
import argparse
import pandas as pd
from binance.client import Client
from binance.enums import KLINE_INTERVAL_1MINUTE
import pandas_ta as ta

def fetch_acum_dist(api_key, api_secret, coin_id):
    try:
        client = Client(api_key, api_secret)
        klines = client.get_historical_klines(coin_id, KLINE_INTERVAL_1MINUTE, "1 day ago UTC")

        if not klines or len(klines) < 1:
            print("0")
            sys.stdout.flush()
            return

        df = pd.DataFrame(klines, columns=[
            'timestamp', 'open', 'high', 'low', 'close', 'volume',
            'close_time', 'quote_asset_volume', 'number_of_trades',
            'taker_buy_base_asset_volume', 'taker_buy_quote_asset_volume', 'ignore'
        ])
        
        # Convert price and volume columns to float for calculations
        df['high'] = df['high'].astype(float)
        df['low'] = df['low'].astype(float)
        df['close'] = df['close'].astype(float)
        df['volume'] = df['volume'].astype(float)

        # Calculate Accumulation/Distribution line (ADL)
        df.ta.ad(append=True)

        # Column name is usually 'AD' after pandas_ta calculation
        if 'AD' not in df.columns:
            print("0")
            sys.stdout.flush()
            return

        ad_value = df['AD'].iloc[-1]

        if pd.isna(ad_value):
            print("0")
        else:
            print(f"{ad_value}")

        sys.stdout.flush()

    except Exception as e:
        print(f"Error: {str(e)}")
        sys.stdout.flush()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Fetch Accumulation/Distribution from Binance")
    parser.add_argument('api_key', type=str, help='API key')
    parser.add_argument('api_secret', type=str, help='API secret')
    parser.add_argument('coin_id', type=str, help='Trading pair symbol (e.g., BTCUSDT)')

    args = parser.parse_args()
    fetch_acum_dist(args.api_key, args.api_secret, args.coin_id)
