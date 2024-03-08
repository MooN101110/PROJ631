import csv

attributs=[]
with open("golf.csv","r") as f:
    reader = csv.reader(f, delimiter=',')
    for row in reader:
        if attributs==[]: #revoir condition
            for elt in row:
                attributs.append(elt)
        else:
            print(', '.join(row))
  