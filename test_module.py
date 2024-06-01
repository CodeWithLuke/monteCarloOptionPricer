# This is a sample Python script.

# Press ⌃R to execute it or replace it with your code.
# Press Double ⇧ to search everywhere for classes, files, tool windows, actions, and settings.

import sys

import monte_carlo_option_pricer

import datetime as dt

#TODO: make this a pytest file

if __name__ == '__main__':

    print(monte_carlo_option_pricer.add(2, 3))
    
    print(monte_carlo_option_pricer.addDays(dt.datetime.now(), 2))

    print(monte_carlo_option_pricer.calc_monte_carlo_random_walk(2))



