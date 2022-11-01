size, n = map(int, input().split(" "))
durations = [0 for i in range(n)]

if n != 0:
    queue_proc = [[-1, -1, -1] for i in range(size)]
    front, back = 0, 0
    in_proc = [-1, -1, -1]  # arrive duration
    for i in range(n):
        arrive, duration = map(int, input().split(" "))
        if not i:
            in_proc = [arrive, duration, i]
            durations[i] = arrive
            continue

        end_proc = in_proc[0] + in_proc[1]
        if arrive >= end_proc:
            if queue_proc[front] == [-1, -1, -1]:
                in_proc = [arrive, duration, i]
                durations[i] = arrive
            else:
                in_proc = queue_proc[front]
                queue_proc[front] = [-1, -1, -1]
                queue_proc[back] = [arrive, duration, i]

                durations[in_proc[2]] = in_proc[0]

                front = (front + 1) % size
                back = (back + 1) % size
        else:
            if queue_proc[back] == [-1, -1, -1]:
                queue_proc[back] = [arrive, duration, i]
                continue

            if queue_proc[(back + 1) % size] == [-1, -1, -1]:
                back = (back + 1) % size
                queue_proc[back] = [arrive, duration, i]
            else:  # queue is full
                if arrive < end_proc:  # maybe <=
                    durations[i] = -1
                    continue
                else:
                    in_proc = queue_proc[front]
                    durations[in_proc[2]] = queue_proc[front][0]

                    queue_proc[front] = [-1, -1, -1]

                    queue_proc[back] = [arrive, duration, i]

                    front = (front + 1) % size
                    back = (back + 1) % size

print(*durations)
