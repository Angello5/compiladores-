from scanner_comp import Scanner

def main():
    sc = Scanner("input.isi")
    token = None
    while True:
        token = sc.next_token()
        if token != None:
            token.to_string()
        else:
            break

if __name__ == "__main__":
    main()