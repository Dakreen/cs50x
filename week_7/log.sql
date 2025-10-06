-- Keep a log of all SQL queries executed while solving the mystery.

-- All we know: the theft occurred on July 28, 2024, on Humphrey Street.

-- 1/ Check crime_scene_reports for description of the incident
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Output: Theft of the CS50 duck at 10:15am at the Humphrey Street bakery.
-- Interviews were conducted with three witnesses who were present.
-- Note: a separate littering incident occurred later in the day (unrelated).

-- 2/ Review interviews from the three witnesses: Ruth, Eugene, Raymond
-- First query all interviews from that date:
SELECT *
FROM interviews
WHERE year = 2024 AND month = 7 AND day = 28;
-- Then narrow to Ruth, Eugene, and Raymond:
SELECT transcript
FROM interviews
WHERE name IN ('Ruth', 'Eugene', 'Raymond') AND year = 2024 AND month = 7 AND day = 28;
-- Ruth → saw thief leave in a car; check bakery security footage.
-- Eugene → saw thief withdraw money earlier at the Leggett Street ATM.
-- Raymond → thief made a short (<1 minute) phone call, then planned to take the earliest flight out on July 29.

-- 3/ Review bakery security footage
-- Look for cars that exited between 10:00 and 10:20 (time of theft).
SELECT license_plate, hour, minute, activity
FROM bakery_security_logs
WHERE year = 2024 AND month = 7 AND day = 28
  AND hour = 10 AND minute < 20
  AND activity = 'exit';

-- Check ATM withdrawals at Leggett Street earlier the same morning.
SELECT account_number
FROM atm_transactions
WHERE year = 2024 AND month = 7 AND day = 28
  AND atm_location = 'Leggett Street'
  AND transaction_type = 'withdraw';

-- 4/ Identify the earliest flight on July 29
SELECT *
FROM flights
WHERE year = 2024 AND month = 7 AND day = 29
ORDER BY hour
LIMIT 1;
-- Output: flight id 36 at 8:20am.

-- 5/ Look at phone calls lasting under 1 minute on July 28
SELECT caller, receiver, duration
FROM phone_calls
WHERE year = 2024 AND month = 7 AND day = 28
  AND duration < 60;

-- 6/ Link ATM withdrawals to people (name, phone, passport, plate)
SELECT name, phone_number, passport_number, license_plate
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2024 AND month = 7 AND day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw';

-- 7/ Narrow to those whose license plates were seen leaving the bakery (10:00–10:20)
SELECT name, phone_number, passport_number, license_plate
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2024 AND month = 7 AND day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw'
  AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2024 AND month = 7 AND day = 28
      AND hour = 10 AND minute < 20
      AND activity = 'exit'
  );

-- 8/ Filter further by passengers on the earliest flight (id 36, July 29)
SELECT name, phone_number, passport_number, license_plate
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2024 AND month = 7 AND day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw'
  AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2024 AND month = 7 AND day = 28
      AND hour = 10 AND minute < 20
      AND activity = 'exit'
  )
  AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
      SELECT id
      FROM flights
      WHERE year = 2024 AND month = 7 AND day = 29
      ORDER BY hour
      LIMIT 1
    )
  );

-- 9/ Add filter: suspects must have also made a short call (<1 minute)
SELECT name, phone_number, passport_number, license_plate
FROM people
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_transactions.year = 2024 AND month = 7 AND day = 28
  AND atm_transactions.atm_location = 'Leggett Street'
  AND atm_transactions.transaction_type = 'withdraw'
  AND license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE year = 2024 AND month = 7 AND day = 28
      AND hour = 10 AND minute < 20
      AND activity = 'exit'
  )
  AND passport_number IN (
    SELECT passport_number
    FROM passengers
    WHERE flight_id = (
      SELECT id
      FROM flights
      WHERE year = 2024 AND month = 7 AND day = 29
      ORDER BY hour
      LIMIT 1
    )
  )
  AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE year = 2024 AND month = 7 AND day = 28
      AND duration < 60
  );
-- At this stage: only Bruce remains.

-- 10/ Check the call receiver to identify the accomplice
SELECT receiver
FROM phone_calls
WHERE caller = '(367) 555-5533'
  AND year = 2024 AND month = 7 AND day = 28
  AND duration < 60;

-- Find the name of the receiver (the accomplice)
SELECT name
FROM people
WHERE phone_number = '(375) 555-8161';

-- 11/ Find the escape destination
SELECT city
FROM airports
WHERE id = (
  SELECT destination_airport_id
  FROM flights
  WHERE id = (
    SELECT id
    FROM flights
    WHERE year = 2024 AND month = 7 AND day = 29
    ORDER BY hour
    LIMIT 1
  )
);

-- ✅ Final Conclusion:
-- Thief = Bruce
-- Accomplice = Robin
-- City = New York City