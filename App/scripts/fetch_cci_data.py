import sys
import argparse
import pandas as pd
from binance.client import Client
from binance.enums import KLINE_INTERVAL_1MINUTE
import pandas_ta as ta

def fetch_cci(api_key, api_secret, coin_id):
    try:
        client = Client(api_key, api_secret)
        klines = client.get_historical_klines(coin_id, KLINE_INTERVAL_1MINUTE, "1 day ago UTC")
        if not klines or len(klines) < 20:
            print("0")
            sys.stdout.flush()
            return

        df = pd.DataFrame(klines, columns=[
            'timestamp', 'open', 'high', 'low', 'close', 'volume',
            'close_time', 'quote_asset_volume', 'number_of_trades',
            'taker_buy_base_asset_volume', 'taker_buy_quote_asset_volume', 'ignore'
        ])

        df['high'] = df['high'].astype(float)
        df['low'] = df['low'].astype(float)
        df['close'] = df['close'].astype(float)

        df.ta.cci(append=True)

        if 'CCI_14_0.015' not in df:
            print("0")
            sys.stdout.flush()
            return

        cci = df['CCI_14_0.015'].iloc[-1]

        if pd.isna(cci):
            print("0")
        else:
            print(f"{cci}")

        sys.stdout.flush()
    except Exception:
        print("0")
        sys.stdout.flush()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("api_key")
    parser.add_argument("api_secret")
    parser.add_argument("coin_id")
    args = parser.parse_args()
    fetch_cci(args.api_key, args.api_secret, args.coin_id)
