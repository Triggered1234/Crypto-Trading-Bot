import argparse
import logging
from binance.exceptions import BinanceAPIException
from binance.spot import Spot as Client
import os
import json
import sys

def main(api_key, secret_key):
    # Set the path for the log file
    log_file = os.path.join(os.path.dirname(__file__), "error.log")

    # Configure logging
    logging.basicConfig(filename=log_file, level=logging.ERROR, format='%(asctime)s - %(levelname)s - %(message)s')
    
    try:
        # Initialize Binance Spot client
        spot_client = Client(api_key, secret_key)
        
        # Get balance
        balance_info = spot_client.balance()
        
        # Print balance information
        print("Balance Information:")
        try:
            print(json.dumps(balance_info, ensure_ascii=False, indent=4))
        except UnicodeEncodeError as e:
            logging.warning("Failed to print balance information: %s", str(e))

        # Write balance information to a file in the build directory
        build_directory = os.path.join(os.path.dirname(__file__), "..", "build-App-Desktop_Qt_6_6_2_MinGW_64_bit-Debug")
        file_path = os.path.join(build_directory, "balance_info.txt")
        with open(file_path, "w", encoding="utf-8") as file:
            json.dump(balance_info, file, ensure_ascii=False, indent=4)
        
        sys.exit(0)  # Exit the script with success code 0
    except BinanceAPIException as e:
        # Log API errors
        logging.error("Binance API error: %s", str(e))
        sys.exit(1)  # Exit the script with error code 1
    except Exception as e:
        # Log any other exceptions that occur
        logging.exception("An error occurred: %s", str(e))
        sys.exit(1)  # Exit the script with error code 1

if __name__ == "__main__":
    # Parse command-line arguments
    parser = argparse.ArgumentParser()
    parser.add_argument("api_key", help="Binance API Key")
    parser.add_argument("secret_key", help="Binance Secret API Key")
    args = parser.parse_args()

    # Call main function with API keys as arguments
    main(args.api_key, args.secret_key)
