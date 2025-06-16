import sys
import argparse
import pandas as pd
from binance.client import Client
from binance.enums import KLINE_INTERVAL_1MINUTE

def fetch_volume(api_key, api_secret, coin_id):
    try:
        client = Client(api_key, api_secret)
        klines = client.get_historical_klines(coin_id, KLINE_INTERVAL_1MINUTE, "1 day ago UTC")
        if not klines:
            print("0")
            sys.stdout.flush()
            return

        # Ultima lumânare
        latest = klines[-1]
        volume = float(latest[5])

        print(f"{volume}")
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
    fetch_volume(args.api_key, args.api_secret, args.coin_id)
