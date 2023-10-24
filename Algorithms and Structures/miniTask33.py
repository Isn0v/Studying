prices = [7,1,5,3,6,4]

def maxProfit(prices):
    profit = 0
    min_n = prices[0]
    for i in range(1, len(prices)):
        min_n = min(min_n, prices[i])
        if prices[i] - min_n > 0:
            profit += prices[i] - min_n
            min_n = prices[i]
    return profit
    