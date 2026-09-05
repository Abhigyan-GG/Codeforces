from datetime import datetime

def lg(timestamps):
    if not timestamps or len(timestamps) < 2:
        return 0

    times = []
    for t in timestamps:
        try:
            times.append(datetime.fromisoformat(t))
        except:
            pass

    times.sort()

    mg = 0

    for i in range(1, len(times)):
        diff = (times[i] - times[i-1]).total_seconds()
        if diff > mg:
            mg = diff
    return mg
