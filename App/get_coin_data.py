# get_coin_data.py
import requests
import sys

def get_coin_data(coin_id):
    url = f"https://api.coingecko.com/api/v3/simple/price?ids={coin_id}&vs_currencies=usd&include_market_cap=true&include_24hr_change=true"
    response = requests.get(url)
    response.raise_for_status()  # Raises an HTTPError if the HTTP request returned an unsuccessful status code
    data = response.json()

    if coin_id in data:
        price = data[coin_id]['usd']
        change_24h = data[coin_id]['usd_24h_change']
        return price, change_24h
    else:
        raise ValueError("Coin ID not found.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python get_coin_data.py <coin_id>")
        sys.exit(1)

    coin_id = sys.argv[1]  # The coin_id is passed as a command-line argument
    try:
        price, change_24h = get_coin_data(coin_id)
        print(f"{coin_id.capitalize()} Price: ${price:.2f}, 24h Change: {change_24h:+.2f}%")
    except Exception as e:
        print("Error:", e)
        sys.exit(1)
