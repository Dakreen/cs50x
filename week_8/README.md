# CS50x – Week 8 Homepage

## Overview
This project is part of **CS50x Week 8**, focusing on **web programming with HTML, CSS, and JavaScript**.  
It implements a professional, responsive personal homepage that supports **English and French translation** through a JSON-based language system.

The goal is to demonstrate:
- Web structure design using HTML5 and Bootstrap  
- Styling customization with CSS  
- Dynamic content translation using JavaScript and JSON  
- Clean, maintainable code across multiple pages  

Example:  
> The website automatically switches all text between English and French when the user clicks “EN” or “FR”.

---

## How It Works
The project consists of four interconnected pages (`index.html`, `about.html`, `projects.html`, `contact.html`) styled with **Bootstrap 5** and a custom CSS theme.  
Language switching is handled by **JavaScript**, which loads content dynamically from a `translations.json` file.

### Logic Flow
1. When the page loads, `script.js` fetches `translations.json`.
2. All elements with the `data-lang` attribute are identified.
3. When the user clicks **EN** or **FR**, the script:
   - Changes all text content to the selected language.  
   - Updates placeholders (e.g., in the contact form).  
   - Updates the `<html lang>` attribute for accessibility.
4. Translations are stored in a structured JSON file with identical key hierarchies for `en` and `fr`.

### Example JSON Structure
```json
{
  "en": {
    "nav": { "home": "Home", "about": "About" },
    "contact": { "title": "Get in Touch", "placeholderName": "Your Name" }
  },
  "fr": {
    "nav": { "home": "Accueil", "about": "À propos" },
    "contact": { "title": "Me Contacter", "placeholderName": "Votre nom" }
  }
}
```

---

## File Structure
```
week_8/
├── index.html           # Main homepage
├── about.html           # About section
├── projects.html        # Portfolio of personal projects
├── contact.html         # Contact form with EN/FR support
├── styles.css           # Custom dark theme styling
├── script.js            # Handles translation logic
├── translations.json    # Stores EN/FR text content
└── images/
    ├── hero_bg.png
    ├── network_lab.png
    ├── coreventra.png
    └── domotic.png
```

### File Descriptions
- **`index.html`** – Homepage introducing the author and featured projects.  
- **`about.html`** – Background, skills, and certifications.  
- **`projects.html`** – Detailed project cards (Hybrid Network Lab, Coreventra, Domotic).  
- **`contact.html`** – Contact form and social links.  
- **`styles.css`** – Custom dark cyber theme and Bootstrap overrides.  
- **`script.js`** – Fetches translations and updates DOM text dynamically.  
- **`translations.json`** – Centralized English–French translation dictionary.

---

## How to Run

### Option 1 — Local Preview
You can open `index.html` directly in your browser:
```bash
file:///path/to/week_8/index.html
```

> ⚠️ Note: The translation system (`fetch`) might not work in some browsers when opened directly from a file path.

### Option 2 — Local Web Server (Recommended)
To enable JSON loading, start a simple local server:
```bash
cd week_8
python -m http.server
```
Then open:
```
http://localhost:8000
```

---

## Note
- The translation system depends on **`translations.json`**, so the project must be run from a local server.  
- All pages share the same **navbar, footer, and language system** for consistency.  
- Built with **Bootstrap 5.3.3** and **Bootstrap Icons**.  
- The contact form is currently **disabled** (demo only).  
- The script dynamically updates placeholders and `<html lang>` for accessibility.  

### Future Improvements
- Save user’s language preference with `localStorage`.  
- Add a **dark/light mode** toggle.  
- Deploy publicly via **GitHub Pages** or **Netlify**.  
- Implement email form submission through Formspree or backend API.  

---

## Visual Design
The site uses a **dark cyber-style theme** with cyan accents.  
Custom classes in `styles.css` add polish:
- `.bg-light-dark` – custom dark-gray background  
- `.py-7` – extra spacing for large sections  
- Navbar blur and transparency with `backdrop-filter`  
- Consistent accent color `#00f2ff` for active links and icons  

Example:
```css
.nav-link.active {
  color: #00f2ff !important;
  font-weight: 600;
}
.card i {
  color: #00f2ff;
}
```

---

## JavaScript Summary
**`script.js`** controls all translation logic.

### Main Features
- Loads translations asynchronously with `fetch()`.
- Updates every `[data-lang]` element’s text.  
- Switches placeholders for contact form inputs.  
- Changes `<html lang>` dynamically.  
- Toggles active state between **EN** and **FR** links.

### Example
```js
// Switch page text
function switch_lang(lang, data) {
  document.querySelectorAll("[data-lang]").forEach(e => {
    const [section, key] = e.getAttribute("data-lang").split(".");
    if (data[lang][section][key]) e.innerText = data[lang][section][key];
  });
}
```

---

## Translations
All content is stored in `translations.json` with **English (`en`)** and **French (`fr`)** objects.  
Each page section (`nav`, `hero`, `about`, `projectsPage`, `contact`, etc.) has mirrored keys.

Example snippet:
```json
{
  "en": {
    "contact": {
      "title": "Get in Touch",
      "desc": "Feel free to reach out...",
      "btnSend": "Send Message"
    }
  },
  "fr": {
    "contact": {
      "title": "Me Contacter",
      "desc": "N’hésitez pas à me contacter...",
      "btnSend": "Envoyer le message"
    }
  }
}
```

---

## Technologies Used
- **HTML5** – semantic web structure  
- **CSS3 + Bootstrap 5.3.3** – responsive design and layout  
- **JavaScript (ES6)** – translation logic and DOM manipulation  
- **JSON** – structured multilingual data storage  

---

## Author
- **Name:** Jerome Henry
- **Date:** October 2025
