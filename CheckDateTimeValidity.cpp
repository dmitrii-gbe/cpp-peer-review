const int MIN_YEAR_MONTH_DAY = 1;
const int MIN_HOUR_MINUTE_SECOND = 0;
const int MAX_HOUR = 23;
const int MAX_MINUTE_SECOND = 59;
const int MAX_YEAR = 9999;
const int MAX_MONTH =  12;

bool CheckIfLeapYear(const DateTime& dt){
    return (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
}

array<int, 12> CalculateMonthLengths(bool is_leap_year){
    return {31, 28 + static_cast<int>(is_leap_year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
}

void CheckDateTimeValidity(const DateTime& dt) {
    if (dt.year < MIN_YEAR_MONTH_DAY) {
        throw domain_error("year is too small"s);
    }
    if (dt.year > MAX_YEAR) {
        throw domain_error("year is too big"s);
    }

    if (dt.month < MIN_YEAR_MONTH_DAY) {
        throw domain_error("month is too small"s);
    }
    if (dt.month > MAX_MONTH) {
        throw domain_error("month is too big"s);
    }

    const array<int, 12> month_lengths = CalculateMonthLengths(CheckIfLeapYear(dt));

    if (dt.day < MIN_YEAR_MONTH_DAY) {
        throw domain_error("day is too small"s);
    }
    if (dt.day > month_lengths[dt.month - 1]) {
        throw domain_error("day is too big"s);
    }

    if (dt.hour < MIN_HOUR_MINUTE_SECOND) {
        throw domain_error("hour is too small"s);
    }
    if (dt.hour > MAX_HOUR) {
        throw domain_error("hour is too big"s);
    }

    if (dt.minute < MIN_HOUR_MINUTE_SECOND) {
        throw domain_error("minute is too small"s);
    }
    if (dt.minute > MAX_MINUTE_SECOND) {
        throw domain_error("minute is too big"s);
    }

    if (dt.second < MIN_HOUR_MINUTE_SECOND) {
        throw domain_error("second is too small");
    }
    if (dt.second > MAX_MINUTE_SECOND) {
        throw domain_error("second is too big"s);
    }
} 