#script takes a string input and checks if there are any repeating characters in it

def get_user_input():
    user_input = input('Type string to analyze: ')
    while len(user_input) < 1:
        print('Enter a valid string')
        user_input = input('Type a string to analyze: ')
    user_input= user_input.lower()
    user_input = user_input.strip()
    return user_input

def has_repeating(datum):
    previous = datum[0]
    for c in datum[1:]:
        if c == previous:
            return True
        previous = c
    return False

def main():
    datum = get_user_input()
    if has_repeating(datum):
        print('It is repeating')
    else:
        print('No repeating characters')

if __name__ == '__main__':
    main()
    print('Complete.')