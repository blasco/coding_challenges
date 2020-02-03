#!/usr/bin/python

def sol(a):
    a = sorted(a)
    for index, val in enumerate(a):
        if index+1 != val:
            return index+1
    return len(a) + 1

def main():
    print(sol([4,2,6,1,5]))

if __name__ == "__main__":
    main()
