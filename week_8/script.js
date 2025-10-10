// Switch all page text to the chosen language
function switch_lang(lang, data) {
    // Get all elements that need translation
    let e = document.querySelectorAll("[data-lang]");
    for (let i = 0; i < e.length; i++) {
        // Get translation key (e.g., "contact.name")
        let sub_e = e[i].getAttribute("data-lang").split(".");
        // If translation exists, update the element
        if (data[lang][sub_e[0]][sub_e[1]]) {
            e[i].innerText = data[lang][sub_e[0]][sub_e[1]];
        }
    }
}

// Main function to load translations and set events
async function main() {
    // Load translations from JSON file
    const response = await fetch("translations.json");
    const data = await response.json();

    // Get language buttons
    let en_lang = document.querySelector("#en");
    let fr_lang = document.querySelector("#fr");

    // When EN button is clicked
    en_lang.addEventListener("click", function() {
        // Mark EN active, FR inactive
        en_lang.classList.add("active");
        fr_lang.classList.remove("active");
        // Switch all text to English
        switch_lang("en", data);
        // Update <html lang>
        document.documentElement.lang = "en";
        // Update placeholders
        document.querySelector("#name").setAttribute("placeholder", data.en.contact.placeholderName);
        document.querySelector("#email").setAttribute("placeholder", data.en.contact.placeholderEmail);
        document.querySelector("#message").setAttribute("placeholder", data.en.contact.placeholderMessage);
    });

    // When FR button is clicked
    fr_lang.addEventListener("click", function() {
        // Mark FR active, EN inactive
        fr_lang.classList.add("active");
        en_lang.classList.remove("active");
        // Switch all text to French
        switch_lang("fr", data);
        // Update <html lang>
        document.documentElement.lang = "fr";
        // Update placeholders
        document.querySelector("#name").setAttribute("placeholder", data.fr.contact.placeholderName);
        document.querySelector("#email").setAttribute("placeholder", data.fr.contact.placeholderEmail);
        document.querySelector("#message").setAttribute("placeholder", data.fr.contact.placeholderMessage);
    });
}

// Run program
main();
