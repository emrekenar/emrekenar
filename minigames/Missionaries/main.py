# Author: Emre Kenar    github.com/emrekenar
# Program: Cannibals and Missionaries

def welcome():
    print("Welcome to Cannibals and Missionaries.\nThis is a text based game "
          "where the goal is to move everybody across the river.\n"
          "However, if there is more cannibals than missionaries at either "
          "side at any time, you lose.\nUse 'c' for cannibals and 'm' for "
          "missionaries.\nFor example, if you want to move a cannibal and "
          "a missionary, type 'cm' or 'mc'.\nGood luck.")

def check_lose(pos):
    # # cannibals > # missionaries on either left or right side is failure
    return pos[0][0] > pos[1][0] > 0 or pos[0][1] > pos[1][1] > 0

def check_win(pos):
    # everybody being on left side is success
    return pos[1][0] == 3 and pos[0][0] == 3

def move(dir, passengers, pos):
    can_cnt = passengers.count(1)
    mis_cnt = passengers.count(2)
    pos[0][not dir] -= can_cnt
    pos[1][not dir] -= mis_cnt
    pos[0][dir] += can_cnt
    pos[1][dir] += mis_cnt

def get_passengers(port, pos):
    passengers = [0, 0]
    ui = ''
    while not valid_input(ui, port, pos):
        ui = input('Who is crossing the river? ').lower()
    for c in ui:
        if c == 'c':
            passengers[passengers.index(0)] = 1
        else:
            passengers[passengers.index(0)] = 2
    return passengers

def valid_input(ui, port, pos):
    if ui not in ['c', 'cc', 'cm', 'mc', 'mm', 'm']:
        return False
    return ui.count('c') <= pos[0][port] and ui.count('m') <= pos[1][port]

def display(pos, port):
    s = '                                   \n' \
        '          /            /           \n' \
        '          /            /           \n' \
        '    {cl} C   /            /    {cr} C    \n' \
        '    {ml} M   /            /    {mr} M    \n' \
        .format(cl=pos[0][0], cr=pos[0][1], ml=pos[1][0], mr=pos[1][1])
    if (port):
        s += '          /      \__/  /           \n'
    else:
        s += '          /  \__/      /           \n'
    print(s)

def run(pos, port=1):
    welcome()
    display(pos, port)
    while (True):
        move(not port, get_passengers(port, pos), pos)
        port = not port
        display(pos, port)
        if check_lose(pos):
            print("Cannibals ate missionaries. You lost.")
            break
        if check_win(pos):
            print("Congratulations, you win.")
            break

if __name__ == '__main__':
    pos = [[0, 3], [0, 3]] # outer: can, mis; inner: left, right
    run(pos)

