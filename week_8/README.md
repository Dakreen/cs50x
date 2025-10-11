# Homepage (CS50 Week 8 – HTML, CSS, JavaScript)

## Overview
This project was developed for **CS50x Week 8**, demonstrating the use of **HTML**, **CSS**, **Bootstrap**, and **JavaScript** to create a responsive, multi-language personal homepage.

The homepage includes sections for **About**, **Projects**, **Certifications**, and **Contact**, and features a **dark modern design** with accent colors and a fully functional **language switcher (English/French)**.

---

## How It Works

### Core Logic
1. When the page loads, translations are fetched from `translations.json`.
2. Clicking a language button (`#en` or `#fr`) triggers:
   - Translation of all text nodes marked with `[data-lang]`.
   - Update of placeholders in form inputs with `setAttribute()`.
   - Update of the `<html lang="...">` attribute for accessibility and SEO.
   - Visual highlight of the active language button using the `.active` class.
3. The JavaScript resolves **nested JSON keys** (e.g., `nav.about`, `contact.name`) safely using string splitting.

---

## Page Sections
- **Navbar:** Transparent with blur effect and cyan hover/active accents.  
- **Hero Section:** Full-width background image with centered intro text.  
- **Projects/Certifications:** Cards with Bootstrap badges and icons.  
- **Contact Form:** Labels, placeholders, and a send button that update with language selection.  
- **Footer:** Social media links (GitHub, LinkedIn, Email) and copyright notice.

---

## Technologies Used
- **HTML5:** Semantic page structure with clear separation of sections.  
- **CSS3:** Custom styling for dark theme and layout spacing.  
- **Bootstrap 5:** Responsive grid system, utilities, and form components.  
- **JavaScript (ES6):** Dynamic translation system and DOM manipulation.  

---

## Design and Implementation
- The website uses a **dark background** with light text for accessibility and aesthetics.  
- Accent color `#00f2ff` provides consistency across links, icons, and buttons.  
- The **navbar** uses `backdrop-filter` for a modern blurred look.  
- Placeholders are styled using `::placeholder` for visibility on dark inputs.  
- The script updates text and placeholders using `innerText` and `setAttribute()` respectively.  
- `<html lang>` is updated dynamically to enhance **SEO** and **screen reader** accuracy.  

---

## Challenges
- Handling **nested translation keys** (e.g., `nav.about`) → solved with a reducer function.  
- Translating **placeholder attributes** → implemented with `setAttribute("placeholder", value)`.  
- Maintaining **inner HTML structure** (badges/spans) → avoided overwriting non-translatable markup.  

---

## Author
- **Name:** Jerome Henry   
- **Date:** October 2025  
