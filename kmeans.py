import sys

global DIM = None
global K = None
global ITER = 400
global points = []



def parse(inp):
    for line in inp:
        coaordinates = line.strip().split(",")
        coaordinates = [float(co) for co in coaordinates]
        if DIM == None:
            DIM = len(coaordinates)
        if len(coaordinates) != DIM:
            if not line and len(inp) == len(points):
                return
            else:
                raise Exception()
        points.append(Point(coaordinates))
    return

def main():
    #update K and ITER
    try:
        K = int(sys.argv[1])
    except Exception:
        print("Incorrect number of clusters!")
        return
    if K < 2:
        print("Incorrect number of clusters!")
        return
    if len(sys.argv) > 2:
        try:
            ITER = int(sys.argv[2])
        except Exception:
            print("Incorrect number of iterations!")
        if (ITER < 2) or (ITER > 799):
            print("Incorrect number of iterations!")
            return

    #parse and dreate points
    parse(sys.stdin)


if __name__ == "__main__":
    try:
        main()
    except Exception:
        print("An Error Has Occured")



