import random
from PIL import Image
import io

# heart rate sensor function 

    
def heart_sensor():
    pass


# distortion pass function

# we have to create categories of 
# low, mid, high heart rate state
# duration of each category
# heart rate state * duration  = distortion intensity

# for distortion intensity 
# how large the chunk size should be, time in between each distortion pass

# how large the chunk size should be based off heart rate state
# time in between each distortion pass based off duration of the state

# data being recorded for 12 hrs
# 3 of those hours, my heart rate state is low 
# the chunk size = 50 because its low 
# because it lasted for 3 hours, each pass will be spaces 30 mins apart 


# have to create a rule system for each category 

# define the heart rate state based on the heart rate sensor data
# low: below 60 bpm
# mid: 60-100 bpm
# high: above 100 bpm

heart_rate_state = {
    "low": [],
    "mid": [],
    "high": []
}
# chunk size based on heart rate state 
chunk_size = {heart_rate_state["low"]: 50, heart_rate_state["mid"]: 75, heart_rate_state["high"]: 100}


duration_state_pass_baseline = {heart_rate_state["low"]: 2, heart_rate_state["mid"]: 4, heart_rate_state["high"]: 6}
# how many hours the state has been 
duration_hr = {}
duration_state_pass_multiplier = {heart_rate_state["low"]: 0.5, heart_rate_state["mid"]: 0.75, heart_rate_state["high"]: 1}



# duration_time = # of hours each state has been active
for state in heart_rate_state:
    duration_time[state] = 0


# calculate the duration of each state pass based on the baseline and multiplier 
duration_state_passes = {
    state: duration_state_pass_baseline[state] * duration_state_pass_multiplier[state]
    if duration_time[state] > 0
    else duration_state_pass_baseline[state]


    for state in heart_rate_state
}

# duration state passed = state
# 


# example:
# low heart rate state: chunk size = 50
# mid heart rate state: chunk size = 75
# high heart rate state: chunk size = 100

# if heart rate state is low, duration pass = 30 mins
# if heart rate state is mid, duration pass = 20 mins   
# if heart rate state is high, duration pass = 10 mins

# distortion intensity = heart_rate_state + duration_pass

# duration_thresholds
# low heart rate state duration at 1 hour = 2 passes
# mid heart rate state duration at 1 hour = 4 passes
# high heart rate state duration at 1 hour = 6 passes




# after each hour in the heart rate state, it multiplies by (low = 0.5, mid = 0.75, high = 1)
# duration_thresholds = 
# if heart rate state is low && below 3 hours 
distortion_intensity = {}


def distort_pass(data):
    start = 500
    end = len(data) - 2
    
    # do a few swaps per pass
    for _ in range(5):
        chunk_size = random.randint(50, 100)
        chunk_start = random.randint(start, end - chunk_size)
        chunk = data[chunk_start : chunk_start + chunk_size]
        paste_at = random.randint(start, end - chunk_size)
        data[paste_at : paste_at + chunk_size] = chunk
    
    return data

def compress_pass(data, quality=15):
    buffer = io.BytesIO(data)
    img = Image.open(buffer)
    out = io.BytesIO()
    img.save(out, format='JPEG', quality=quality)
    return bytearray(out.getvalue())

# Load original
with open('pythondistort6.jpg', 'rb') as f:
    data = bytearray(f.read())

# Run 20 passes, save each generation
for i in range(5):
    data = distort_pass(data)
    data = compress_pass(data)
    with open(f'pass_{i:03d}.jpg', 'wb') as f:
        f.write(data)
    print(f'Pass {i+1} done')