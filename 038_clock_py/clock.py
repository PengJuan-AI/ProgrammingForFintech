class MyClock24:
    """represent a 24-hour clock."""
    def __init__(self, h, m, s):
        self.hours = int(h%24)
        self.minutes = int(m%60)
        self.seconds = int(s%60)
    def __str__(self):
        return "{:02d}:{:02d}:{:02d}".format(self.hours, self.minutes, self.seconds)

    def __repr__(self):
        return str(self.__dict__)

    def tick(self):
        if self.seconds >= 59:
            self.seconds = 0
            self.minutes += 1
            if self.minutes>= 59:
                self.minutes=0
                self.hours += 1
                if self.hours>=23:
                    self.hours=0
        else:
            self.seconds+=1
    def __eq__(self, other):
        if self.seconds == other.second and self.seconds == other.second and self.seconds == other.second:
            return True
        else:
            return False
    def __ne__(self, other):
        if self.seconds != other.second and self.seconds != other.second and self.seconds != other.second:
            return True
        else:
            return False

    def __ge__(self, other):
        if self.hours>other.hour:
            return True
        elif self.hours==other.hour:
            if self.minutes > other.minute:
                return True
            elif self.minutes == other.minute:
                if self.seconds >= other.second:
                    return True
                else:
                    return False
            else:
                return False
        else:
            return False

    def __gt__(self, other):
        if self.hours>other.hour:
            return True
        elif self.hours==other.hour:
            if self.minutes > other.minute:
                return True
            elif self.minutes == other.minute:
                if self.seconds > other.second:
                    return True
                else:
                    return False
            else:
                return False
        else:
            return False

    def __le__(self, other):
        if self.hours<other.hour:
            return True
        elif self.hours==other.hour:
            if self.minutes < other.minute:
                return True
            elif self.minutes == other.minute:
                if self.seconds <= other.second:
                    return True
                else:
                    return False
            else:
                return False
        else:
            return False

    def __lt__(self, other):
        if self.hours<other.hour:
            return True
        elif self.hours==other.hour:
            if self.minutes < other.minute:
                return True
            elif self.minutes == other.minute:
                if self.seconds < other.second:
                    return True
                else:
                    return False
            else:
                return False
        else:
            return False

    def __add__(self, other):
        if isinstance(other, MyClock24):
            s = self.seconds+other.second
            a = s / 60
            b = s % 60
            s = int(b)
            m = self.minutes + other.minute + a
            a = m / 60
            b = m % 60
            m = int(b)
            h = self.hours + other.hour + a
            h = int(h % 24)
        else:
            s = self.seconds + other
            a = s/60
            b = s%60
            s = int(b)
            m = self.minutes+a
            a = m/60
            b = m%60
            m = int(b)
            h = self.hours+a
            h = int(h%24)

        return MyClock24(h,m,s)


    def __sub__(self, other):
        if isinstance(other, MyClock24):
            s = self.seconds-other.second
            if s < 0:
                a = abs(s)/60+1
                b = abs(s) % 60
                s = 60 - int(b)
            else:
                a= 0

            m = self.minutes-other.minute-a
            if m<0:
                a = abs(m)/60+1
                b = abs(m) % 60
                m = 60 - int(b)
            else: a = 0
            h = self.hours-other.hour-a
            if h<0:
                b = abs(h)%24
                h = 24-int(b)
        else:
            s = self.seconds-other
            if s < 0:
                a = abs(s)/60+1
                b = abs(s) % 60
                s = 60 - int(b)
            else: a= 0
            m = self.minutes-a
            if m<0:
                a = abs(m)/60+1
                b = abs(m) % 60
                m = 60 - int(b)
            else: a = 0
            h = self.hours-a
            if h<0:
                b = abs(h)%24
                h = 24-int(b)

        return MyClock24(h,m,s)

    @property
    def hour(self):
        return self.hours

    @property
    def minute(self):
        return self.minutes

    @property
    def second(self):
        return self.seconds
