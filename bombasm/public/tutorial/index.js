const title         = document.querySelector(".title");
const subtitle      = document.querySelector(".subtitle");
const currentBit    = document.querySelector(".current-bitstring-screen");
const description   = document.querySelector(".description-section .screen")
const opButtons     = document.querySelector(".main-buttons");

(async () => {
    const params = new URLSearchParams(document.location.search);
    const lvl = params.get("level");

    const response = await fetch('./../json/tutorial-levels.json'); 
    const tutorials = await response.json();
    let tutorial;
    tutorials.forEach(t => 
        (t.number == lvl) ? tutorial = t : {}
    )

    title.textContent       = tutorial.title;
    subtitle.textContent    = tutorial.subtitle;
    currentBit.textContent  = tutorial.start_bitstring; 
    description.textContent = tutorial.desc;

    tutorial.operations.forEach(op => {
        const button = document.createElement("button");
        button.className = "operation-btn";
        button.textContent = op;
        button.addEventListener("click", () => doBitOperation(op));
        opButtons.appendChild(button);
    });

    function doBitOperation(op) {
        [operator, operand] = op.split(" ");

        let newString = ""; 
        switch (operator) {
        case "AND": 
            for (let i = 0; i < tutorial.bitstring_length; i++) {
                newString += (operand[i] & currentBit.textContent[i]);
            }
            break;
        case "OR": 
            for (let i = 0; i < tutorial.bitstring_length; i++) {
                newString += (operand[i] | currentBit.textContent[i]);
            }
            break;
        case "NOT": 
            for (let i = 0; i < tutorial.bitstring_length; i++) {
                newString += (currentBit.textContent[i] ^ 1);
            }
            break;
        case "XOR": 
            for (let i = 0; i < tutorial.bitstring_length; i++) {
                newString += (operand[i] ^ currentBit.textContent[i]);
            }
            break;
        
        case "SHL": {
            let shift = parseInt(operand);
            newString = currentBit.textContent.slice(shift) + "0".repeat(shift);
            break;
        }

        case "SHR": { 
            let shift = parseInt(operand);
            newString = "0".repeat(shift) + currentBit.textContent.slice(0, tutorial.bitstring_length - shift);
            break;
        }

        case "ROL": {
            let shift = parseInt(operand);
            const actualShift = shift % tutorial.bitstring_length;
            newString = currentBit.textContent.slice(actualShift) + currentBit.textContent.slice(0, actualShift);
            break;
        }

        case "ROR": {
            let shift = parseInt(operand);
            const actualShift = shift % tutorial.bitstring_length;
            newString = currentBit.textContent.slice(-actualShift) + currentBit.textContent.slice(0, -actualShift);
            break;
        }
        }
        
        currentBit.textContent = newString;
    }
})();

const resetLevel = document.querySelectorAll(".reset-btn");

resetLevel.forEach(btn => {
    btn.addEventListener("click", () => {
        window.location.reload();
    });
})  
