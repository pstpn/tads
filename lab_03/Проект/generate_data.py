from random import randint


car_models = ["BMW", "Opel", "Kia", "Audi", "Tesla", "Ferrari", "Ford", "Porsche",
          "Honda", "Toyota", "Bentley", "Jeep", "Subaru", "Dodge", "Mazda",
          "Jaguar", "Nissan", "Volvo", "GMC", "Suzuki", "Fiat", "Lotus"]

countries = ["Germany", "Japan", "China", "USA", "Italy", "United Kingdom", "Sweden"]

colors = ["blue", "red", "green", "orange", "yellow", "aqua", "black", "white", "gray"]

count = int(input("Input count: "))

with open("data.txt", "w") as f:
    for i in range(count):
        f.write(car_models[randint(0, len(car_models) - 1)] + ";")
        f.write(countries[randint(0, len(countries) - 1)] + ";")
        f.write(str(randint(10000, 99999999)) + ";")
        f.write(colors[randint(0, len(colors) - 1)] + ";")
        
        tp = str(randint(0, 1))
        f.write(tp + ";")
        
        if tp == "0":
            f.write(str(randint(1, 40)) + ";")
        elif tp == "1":
            f.write(str(randint(1900, 2022)) + ";")
            f.write(str(randint(1, 999999)) + ";")
            f.write(str(randint(0, 20)) + ";")
            f.write(str(randint(1, 20)) + ";")
            
        if i != count - 1:
            f.write("\n")