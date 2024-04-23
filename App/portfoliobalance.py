from binance.client import Client

def get_portfolio_info(api_key, secret_key):
    client = Client(api_key, secret_key)
    
    # Get account information
    account_info = client.get_account()
    balances = account_info['balances']
    
    # Get current prices for all symbols
    tickers = client.get_all_tickers()
    symbol_prices = {ticker['symbol']: float(ticker['price']) for ticker in tickers}
    
    portfolio_data = ""
    total_balance = 0.0
    for balance in balances:
        asset = balance['asset']
        free = float(balance['free'])
        
        if free > 0 and asset + 'USDT' in symbol_prices:
            price = symbol_prices[asset + 'USDT']
            total_value = free * price
            portfolio_data += f"{asset}: Balance: {free}, Price: ${price}, Total Value: ${total_value:.2f}\n"
            total_balance += total_value
    
    portfolio_data += f"Total Balance: ${total_balance:.2f}"  # Remove trailing newline
    
    return portfolio_data

# Example of using the function
api_key = "S4DDhuhW2r7BU8klFngZaIx7OkUGRfEbx7ozR9oaBGZDtlU8H5X0faNRGtu98FF2"
secret_key = "dbTXtfL0odCNOf7mBltRikGawV0014yBypwaEAmzYQU86W5bXE7wwJvS7S7RkDTd"

portfolio_info = get_portfolio_info(api_key, secret_key)
print(portfolio_info)  # Output to be captured by C++
