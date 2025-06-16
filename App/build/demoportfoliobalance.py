import sys
from binance.client import Client

def get_demo_portfolio_info(api_key, secret_key):
    client = Client(api_key, secret_key, testnet=True)

    included_coins = ['BTC', 'ETH', 'BNB', 'ADA', 'XRP', 'USDT']

    account_info = client.get_account()
    balances = account_info['balances']

    tickers = client.get_all_tickers()
    symbol_prices = {ticker['symbol']: float(ticker['price']) for ticker in tickers}

    portfolio_data = ""
    total_balance = 0.0
    for balance in balances:
        asset = balance['asset']
        free = float(balance['free'])

        if free > 0 and asset in included_coins and asset + 'USDT' in symbol_prices:
            price = symbol_prices[asset + 'USDT']
            total_value = free * price
            portfolio_data += f"{asset}: Balance: {free}, Price: ${price}, Total Value: ${total_value:.2f}\n"
            total_balance += total_value

    # Fetch USDT balance
    usdt_balance = next((balance['free'] for balance in balances if balance['asset'] == 'USDT'), 0)
    total_balance += float(usdt_balance)

    portfolio_data += f"USDT: Balance: {usdt_balance}, Total Value: ${usdt_balance}\n"
    portfolio_data += f"Total Balance: ${total_balance:.2f}"

    return portfolio_data

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python demoportfoliobalance.py <api_key> <secret_key>")
        sys.exit(1)

    api_key = sys.argv[1]
    secret_key = sys.argv[2]

    try:
        demo_portfolio_info = get_demo_portfolio_info(api_key, secret_key)
        print(demo_portfolio_info)
    except Exception as e:
        print(f"Error occurred: {e}")
        sys.exit(1)
