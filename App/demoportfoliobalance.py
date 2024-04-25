from binance.client import Client

def get_demo_portfolio_info(api_key, secret_key):
    client = Client(api_key, secret_key, testnet=True)
    
    included_coins = ['BTC', 'ETH', 'BNB', 'ADA', 'XRP']
    
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
    
    portfolio_data += f"Total Balance: ${total_balance:.2f}"
    
    return portfolio_data

api_key = "pQN3vI2m0PlM6SbyeBh8EVvphFHhT8hxvSD3WwfknEmQm7mPRBdQGXofVcFXHT8u"
secret_key = "V4Am9EVSgP72lbeqeRvxIugwco3je1yVMXpYmuFsdQKyLSUXkGShk97R9IXmtMIu"

demo_portfolio_info = get_demo_portfolio_info(api_key, secret_key)
print(demo_portfolio_info)
