from binance.client import Client

def get_available_cryptos(api_key, secret_key):
    client = Client(api_key, secret_key)
    
    # Get all available symbols for spot trading
    exchange_info = client.get_exchange_info()
    symbols = [symbol['symbol'] for symbol in exchange_info['symbols']]
    
    # Get current prices and 24h price changes for all symbols
    tickers = client.get_all_tickers()
    symbol_prices = {ticker['symbol']: float(ticker['price']) for ticker in tickers}
    symbol_24h_changes = {ticker['symbol']: float(ticker['priceChangePercent']) if 'priceChangePercent' in ticker else 0.0 for ticker in tickers}
    
    # Combine symbols with their prices and 24h changes
    cryptos_with_info = []
    for symbol in symbols:
        if symbol in symbol_prices and symbol in symbol_24h_changes:
            price = symbol_prices[symbol]
            price_change_percent = symbol_24h_changes[symbol]
            cryptos_with_info.append(f"{symbol}: Price: {price}, 24h Change: {price_change_percent}%")
    
    return cryptos_with_info

# Example of using the function
api_key = "your_api_key"
secret_key = "your_secret_key"

available_cryptos = get_available_cryptos(api_key, secret_key)
for crypto in available_cryptos:
    print(crypto)
