table,tableq = {},{}
totl,totq = 0,0
def create(b):
    for i in range(b):
        table[i] = None
        tableq[i] = None
def linsert(key,b):
    global totl
    hash = key%b
    flag = 0 
    if table[hash]==None:
        table[hash]=key
    else:
        for i in range(0,b):
            hash = (key+i)%b
            if table[hash]==None:
                table[hash]=key
                totl += 1
                flag += 1
                break
        if flag == 0:
            print("Table Full or Key not probed.")
def qinsert(key,b):
    global totq
    hash = key%b
    flag = 0 
    if tableq[hash]==None:
        tableq[hash]=key
    else:
        for i in range(0,int((b-1)/2)):
            hash = (key+(i*i))%b
            if tableq[hash]==None:
                tableq[hash]=key
                totq += 1
                flag += 1
                break
        if flag == 0:
            print("Table Full or Key not probed.")
def lsearch(key,b):
    hash = key%b
    flag = 0 
    if table[hash]==None:
        print("Key : ",key," is not present.")
    else:
        for i in range(0,b):
            hash = (key+i)%b
            if table[hash]==None:
                print("Key : ",key," is not present.")
                flag += 1
                break
            elif table[hash]==key:
                print("Key : ",key," is present at location : ",hash)
                flag += 1
                break
        if flag == 0:
            print("Key : ",key," is not present.")
def qsearch(key,b):
    hash = key%b
    flag = 0 
    if tableq[hash]==None:
        print("Key : ",key," is not present.")
    else:
        for i in range(0,int((b-1)/2)):
            hash = (key+(i*i))%b
            if tableq[hash]==None:
                print("Key : ",key," is not present.")
                flag += 1
                break
            elif tableq[hash]==key:
                print("Key : ",key," is present at location : ",hash)
                flag += 1
                break
        if flag == 0:
            print("Key : ",key," is not present.")
def printtable(t1, b):
    print("\nLinearly Probed Table:")
    for i in range(b):
        print(t1[i], end="|")
    print("\nQuadratically Probed Table:")
    for i in range(b):
        print(tableq[i], end="|")
    print("\n")

b = int(input("Enter the table size : "))
create(b)
while True:
    ch = int(input("Enter 1-LP | 2-QP | 0-EXIT : "))
    if ch == 0:
        print("EXITED")
        break
    elif ch == 1:
        while True:
            ch2 = int(input("Enter 1-Insert | 2-Search | 0-Back : "))
            if ch2 == 1:
                if totl == b:
                    print("The table is already full.")
                else:
                    key = int(input("Enter the key to be inserted in the table : "))
                    linsert(key, b)
            elif ch2 == 2:
                key = int(input("Enter the key to be searched in the table : "))
                lsearch(key, b)
            elif ch2 == 0:
                print("GOING BACK")
                break
            printtable(table, b)
    elif ch == 2:
        while True:
            ch2 = int(input("Enter 1-Insert | 2-Search | 0-Back : "))
            if ch2 == 1:
                if totq == b:
                    print("The table is already full.")
                else:
                    key = int(input("Enter the key to be inserted in the table : "))
                    qinsert(key, b)
            elif ch2 == 2:
                key = int(input("Enter the key to be searched in the table : "))
                qsearch(key, b)
            elif ch2 == 0:
                print("GOING BACK")
                break
            printtable(tableq, b)