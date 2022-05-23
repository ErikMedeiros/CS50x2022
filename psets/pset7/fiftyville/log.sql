-- https://cs50.harvard.edu/x/2022/psets/7/fiftyville/

-- The theft took place on July 28, 2021 and that it took place on Humphrey Street

-- Search for crime reports on the date and place above
SELECT id, description
FROM crime_scene_reports
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    street LIKE "%Humphrey%";

/*
    Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
    Interviews were conducted today with three witnesses who were present at the time.
    each of their interview transcripts mentions the bakery.
*/

-- Get name and transcript of witnesses
SELECT name, transcript
FROM interviews
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    transcript LIKE "%Bakery%";

/*
    Ruth
    Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery
    parking lot and drive away. If you have security footage from the bakery parking lot,
    you might want to look for cars that left the parking lot in that time frame.

    Eugene
    I don't know the thief's name, but it was someone I recognized. Earlier this morning,
    before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and
    saw the thief there withdrawing some money.

    Raymond
    As the thief was leaving the bakery, they called someone who talked to them
    for less than a minute. In the call, I heard the thief say that they were planning
    to take the earliest flight out of Fiftyville tomorrow.
    The thief then asked the person on the other end of the phone to purchase the
    flight ticket.
*/

-- Find all license plates that left the parking lot between 10:15am and 10:25am
SELECT activity, license_plate, hour, minute
FROM bakery_security_logs
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    hour = 10 AND
    minute BETWEEN 15 AND 25;

-- Find who withdraw money at the ATM on Leggett Street
SELECT account_number
FROM atm_transactions
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    transaction_type = "withdraw" AND
    atm_location LIKE "%Leggett Street%";

-- Find calls that less than a minute after the theft
SELECT caller, receiver, duration
FROM phone_calls
WHERE
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    duration < 60;

-- Cross information of all queries above to find a person
SELECT *
FROM people
WHERE
    license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE
            year = 2021 AND
            month = 7 AND
            day = 28 AND
            hour = 10 AND
            minute BETWEEN 15 AND 25
    ) AND
    id IN (
        SELECT b.person_id
        FROM
            bank_accounts b JOIN atm_transactions a
        ON
            b.account_number = a.account_number
        WHERE
            a.year = 2021 AND
            a.month = 7 AND
            a.day = 28 AND
            a.transaction_type = "withdraw" AND
            a.atm_location LIKE "%Leggett Street%"
    ) AND
    phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE
            year = 2021 AND
            month = 7 AND
            day = 28 AND
            duration < 60
    );

/*
    +--------+-------+----------------+-----------------+---------------+
    |   id   | name  |  phone_number  | passport_number | license_plate |
    +--------+-------+----------------+-----------------+---------------+
    | 514354 | Diana | (770) 555-1861 | 3592750733      | 322W7JE       |
    | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
    +--------+-------+----------------+-----------------+---------------+
*/

-- Get earliest flight out of Fiftyville in the next day
SELECT
    f.id,
    a.city AS "from",
    (SELECT city FROM airports WHERE id = f.destination_airport_id) AS "to",
    f.hour,
    f.minute
FROM
    flights f JOIN airports a
ON
    f.origin_airport_id = a.id
WHERE
    a.full_name LIKE "%Fiftyville%" AND
    f.year = 2021 AND
    f.month = 7 AND
    f.day = 29
ORDER BY f.hour, f.minute
LIMIT 1;

/*
    theft scaped to New York City
    +----+------------+---------------+------+--------+
    | id |    from    |      to       | hour | minute |
    +----+------------+---------------+------+--------+
    | 36 | Fiftyville | New York City | 8    | 20     |
    +----+------------+---------------+------+--------+
*/

-- Get passengers from flight above
SELECT passport_number
FROM passengers
WHERE
    flight_id = (
        SELECT f.id
        FROM
            flights f JOIN airports a
        ON
            f.origin_airport_id = a.id
        WHERE
            a.full_name LIKE "%Fiftyville%" AND
            f.year = 2021 AND
            f.month = 7 AND
            f.day = 29
        ORDER BY f.hour, f.minute
        LIMIT 1
    );

-- Match suspects and the flight passengers
SELECT *
FROM people
WHERE
    license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE
            year = 2021 AND
            month = 7 AND
            day = 28 AND
            hour = 10 AND
            minute BETWEEN 15 AND 25
    ) AND
    id IN (
        SELECT b.person_id
        FROM
            bank_accounts b JOIN atm_transactions a
        ON
            b.account_number = a.account_number
        WHERE
            a.year = 2021 AND
            a.month = 7 AND
            a.day = 28 AND
            a.transaction_type = "withdraw" AND
            a.atm_location LIKE "%Leggett Street%"
    ) AND
    phone_number IN (
        SELECT caller
        FROM phone_calls
        WHERE
            year = 2021 AND
            month = 7 AND
            day = 28 AND
            duration < 60
    ) AND
    passport_number IN (
        SELECT passport_number
        FROM passengers
        WHERE
            flight_id = (
                SELECT f.id
                FROM
                    flights f JOIN airports a
                ON
                    f.origin_airport_id = a.id
                WHERE
                    a.full_name LIKE "%Fiftyville%" AND
                    f.year = 2021 AND
                    f.month = 7 AND
                    f.day = 29
                ORDER BY f.hour, f.minute
                LIMIT 1
            )
    );

/*
    The theft was Bruce
    +--------+-------+----------------+-----------------+---------------+
    |   id   | name  |  phone_number  | passport_number | license_plate |
    +--------+-------+----------------+-----------------+---------------+
    | 686048 | Bruce | (367) 555-5533 | 5773159633      | 94KL13X       |
    +--------+-------+----------------+-----------------+---------------+
*/

-- Get accomplice
SELECT p2.name
FROM
    phone_calls p1 JOIN people p2
ON
    p1.receiver = p2.phone_number
WHERE
    caller = (
        SELECT phone_number
        FROM people
        WHERE
            license_plate IN (
                SELECT license_plate
                FROM bakery_security_logs
                WHERE
                    year = 2021 AND
                    month = 7 AND
                    day = 28 AND
                    hour = 10 AND
                    minute BETWEEN 15 AND 25
            ) AND
            id IN (
                SELECT b.person_id
                FROM
                    bank_accounts b JOIN atm_transactions a
                ON
                    b.account_number = a.account_number
                WHERE
                    a.year = 2021 AND
                    a.month = 7 AND
                    a.day = 28 AND
                    a.transaction_type = "withdraw" AND
                    a.atm_location LIKE "%Leggett Street%"
            ) AND
            phone_number IN (
                SELECT caller
                FROM phone_calls
                WHERE
                    year = 2021 AND
                    month = 7 AND
                    day = 28 AND
                    duration < 60
            ) AND
            passport_number IN (
                SELECT passport_number
                FROM passengers
                WHERE
                    flight_id = (
                        SELECT f.id
                        FROM
                            flights f JOIN airports a
                        ON
                            f.origin_airport_id = a.id
                        WHERE
                            a.full_name LIKE "%Fiftyville%" AND
                            f.year = 2021 AND
                            f.month = 7 AND
                            f.day = 29
                        ORDER BY f.hour, f.minute
                        LIMIT 1
                    )
            )
    ) AND
    year = 2021 AND
    month = 7 AND
    day = 28 AND
    duration < 60;

/*
    The accomplice was Robin
    +-------+
    | name  |
    +-------+
    | Robin |
    +-------+
*/
