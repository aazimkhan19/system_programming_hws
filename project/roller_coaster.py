import threading
from threading import Thread
from threading import Semaphore
from time import sleep
from random import *

numOfPassengers = 4
numOfCars = 2
waitTime = 5
runTime = 60
numOfSeats = 2

available = Semaphore(0)
entered = Semaphore(0)
filled = Semaphore(0)
free = Semaphore(0)

def wait_passenger(time):
    sleep(time)

def wait(x, s):
    x.acquire()
    print(s,'\n')

def signal(x, s):
    x.release()
    print(s,'\n')

def Passenger(id):
    while True:
        wait_passenger(1+randint(0,waitTime))
        print("passenger %d boarding\n"%(id))
        wait(available,'enter')
        signal(entered,'taken')
        wait(filled,'inside')
        print("passenger %d is running\n"%(id))
        wait(free,'free')
        print("passenger %d unboarding\n"%(id))
        
def Car(id):
    while True:
        print("car %d loading\n"%(id))
        for i in range(numOfSeats):
            signal(available,'ready')
        for i in range(numOfSeats):
            wait(entered,'OK')
        for i in range(numOfSeats):
            signal(filled,'reserved')
        print("car %d is running\n"%(id))
        wait_passenger(1+randint(0,waitTime*1))
        print("car %d unloading\n"%(id))
        for i in range(numOfSeats):
            signal(free,'opened')


def RollerCoaster():
    for i in range(numOfPassengers):
        t = Thread(target=Passenger, name=str(i), args=([i]))
        t.start()
    for i in range(numOfCars):
        t = Thread(target=Car, name=str(i), args=([i]))
        t.start()

RollerCoaster()
