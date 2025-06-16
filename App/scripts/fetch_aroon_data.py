import sys
import argparse
import pandas as pd
from binance.client import Client
from binance.enums import KLINE_INTERVAL_1MINUTE
import pandas_ta as ta

def fetch_aroon(api_key, api_secret, coin_id):
    try:
        client = Client(api_key, api_secret)
        klines = client.get_historical_klines(coin_id, KLINE_INTERVAL_1MINUTE, "1 day ago UTC")
        if not klines or len(klines) < 25:
            print("0 0")
            sys.stdout.flush()
            return

        df = pd.DataFrame(klines, columns=[
            'timestamp', 'open', 'high', 'low', 'close', 'volume',
            'close_time', 'quote_asset_volume', 'number_of_trades',
            'taker_buy_base_asset_volume', 'taker_buy_quote_asset_volume', 'ignore'
        ])

        df['high'] = df['high'].astype(float)
        df['low'] = df['low'].astype(float)

        df.ta.aroon(append=True)

        if 'AROOND_25' not in df or 'AROONU_25' not in df:
            print("0 0")
            sys.stdout.flush()
            return

        down = df['AROOND_25'].iloc[-1]
        up = df['AROONU_25'].iloc[-1]

        if pd.isna(up) or pd.isna(down):
            print("0 0")
        else:
            print(f"{up} {down}")

        sys.stdout.flush()
    except Exception:
        print("0 0")
        sys.stdout.flush()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("api_key")
    parser.add_argument("api_secret")
    parser.add_argument("coin_id")
    args = parser.parse_args()
    fetch_aroon(args.api_key, args.api_secret, args.coin_id)
