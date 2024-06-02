# This is a sample Python script.

# Press ⌃R to execute it or replace it with your code.
# Press Double ⇧ to search everywhere for classes, files, tool windows, actions, and settings.

import sys

import monte_carlo_option_pricer

import datetime as dt

import pytest

#TODO: make this a pytest file

def test_monte_carlo_function():
    today = dt.date.today()

    expiry = today + dt.timedelta(days=100)

    monte_carlo_option_pricer.calc_monte_carlo_random_walk(10000, 100.0, today, expiry, 0.15, 0.30)
