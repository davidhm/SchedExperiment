import requests
r = requests.get('https://api.fib.upc.edu/v2/quadrimestres/?format=json')
print(r.text)
