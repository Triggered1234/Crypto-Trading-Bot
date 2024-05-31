from binance.client import Client

def get_available_cryptos(api_key, secret_key):
    client = Client(api_key, secret_key)
    
    # Get all available symbols for spot trading
    exchange_info = client.get_exchange_info()
    symbols = [symbol['symbol'] for symbol in exchange_info['symbols'] if symbol['symbol'].endswith('USDT')]
    
    # Get ticker information for all symbols
    tickers = client.get_ticker()  # Retrieve all ticker information in a single call
    
    # Filter and format ticker data for USDT pairs
    cryptos_with_info = []
    for ticker in tickers:
        symbol = ticker['symbol']
        if symbol in symbols:
            price = float(ticker['lastPrice'])
            price_change_percent = float(ticker['priceChangePercent'])
            # Remove 'USDT' from the symbol
            symbol_name = symbol.replace('USDT', '')
            cryptos_with_info.append(f"{symbol_name}: Price: {price}, 24h Change: {price_change_percent}%")
    
    return cryptos_with_info

# Example of using the function
api_key = "your_api_key"
secret_key = "your_secret_key"

available_cryptos = get_available_cryptos(api_key, secret_key)
for crypto in available_cryptos:
    print(crypto)
