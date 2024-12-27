--- ΔΙΑΡΚΕΙΑ 2 ΩΡΕΣ ---

1. 
	α. Πληκτρολόγιο > Polling ή Interrupts και γιατί ? 
	β. Σκληρό Δίσκο > Polling ή Interrupts και γιατί ? 

Απάντηση:

When it comes to communicating with a keyboard, a common approach is to use interrupts. Here's how it typically works:

α. Interrupt-based Communication:
   - The keyboard is connected to the computer's input/output controller or a dedicated keyboard controller.
   - The keyboard controller is responsible for handling the low-level communication with the keyboard and generating interrupts to notify the CPU of any keyboard events.
   - When a key is pressed or released on the keyboard, the keyboard controller sends an interrupt signal to the CPU.
   - Upon receiving the interrupt, the CPU suspends its current operation, saves its state, and transfers control to an interrupt handler specifically designed to handle keyboard interrupts.
   - The interrupt handler reads the keyboard data from a keyboard buffer, which holds the key scan codes or other information about the key event.
   - The handler processes the keyboard data, interprets the key presses or releases, and performs the necessary actions based on the key events (e.g., updating display, triggering specific functions, etc.).
   - Interrupt-based communication allows the CPU to be responsive and efficiently handle keyboard events without continuously polling the keyboard for input.

Interrupt-based communication with the keyboard offers several advantages, such as reduced CPU utilization, faster response times, and the ability to handle multiple simultaneous key presses (known as "keyboard rollover"). It allows the system to focus on other tasks while waiting for keyboard input, improving overall system performance.

β.

When it comes to communicating with a hard drive, there are two common approaches: polling and interrupts. Here's a brief explanation of each:

1. Polling:
   - Polling is a technique where the system repeatedly checks the status of the hard drive to determine if it is ready to send or receive data.
   - In this method, the CPU regularly queries the hard drive by sending commands and checking the status registers to see if the requested operation has completed.
   - The CPU dedicates its time to actively checking the status, which can be a resource-intensive process, as it constantly consumes CPU cycles even when the hard drive has no data to transfer.
   - Polling can be simpler to implement but may result in higher CPU utilization and response times, especially in scenarios with slow or unpredictable hard drive operations.

2. Interrupts:
   - Interrupts are a mechanism where the hard drive signals the CPU when it requires attention or when a specific event occurs.
   - Instead of actively polling the hard drive, the CPU can perform other tasks until an interrupt signal is received.
   - When an interrupt occurs, the CPU temporarily suspends its current operation, saves its state, and transfers control to an interrupt handler, a specific routine designed to handle the interrupt.
   - The interrupt handler then processes the interrupt, which could involve reading or writing data to/from the hard drive, updating status information, or performing other necessary tasks.
   - Interrupts can reduce CPU utilization and improve response times since the CPU is not constantly checking the hard drive's status.
   - However, interrupt-driven systems require more complex hardware and software design to handle and prioritize interrupts appropriately.

In practice, the choice between polling and interrupts depends on various factors, including the specific requirements of the system, the capabilities of the hard drive controller, and the desired trade-offs between CPU utilization and responsiveness. Different systems may employ a combination of both techniques, using interrupts for critical events and polling for less time-sensitive operations.
It's worth noting that there are alternative methods like polling, where the CPU repeatedly checks the keyboard status to detect key events. However, interrupt-based communication is commonly preferred for keyboards due to its efficiency and responsiveness.

2. Τρεις διαφορές ενός ενσωματωμένου με έναν υπολογιστή

Απάντηση:

1. Design and Purpose:
   - Personal Computer (PC): A personal computer is a general-purpose computing device designed for a wide range of applications. It is typically used by individuals for tasks such as browsing the internet, word processing, multimedia playback, gaming, and running various software applications.
   - Embedded System: An embedded system is a specialized computer system designed to perform specific functions within a larger system or device. It is typically dedicated to a specific task and often operates in an autonomous or semi-autonomous manner. Embedded systems are commonly found in everyday devices like smartphones, digital cameras, home appliances, automotive systems, industrial machinery, and medical equipment.

2. Hardware Architecture:
   - PC: Personal computers typically have a modular and flexible hardware architecture. They consist of standard components like a motherboard, processor, memory, storage devices, input/output ports, and expansion slots. PCs are designed to be easily upgradable and customizable.
   - Embedded System: Embedded systems are built with a specific hardware configuration optimized for their intended function. They often use specialized integrated circuits, microcontrollers, or System-on-Chip (SoC) designs that integrate multiple components onto a single chip. Embedded systems are usually compact, energy-efficient, and designed for reliability.

3. Operating System and User Interface:
   - PC: Personal computers usually run general-purpose operating systems such as Windows, macOS, or Linux. These operating systems provide a graphical user interface (GUI) and support multitasking, allowing users to run multiple applications simultaneously and switch between them easily.
   - Embedded System: Embedded systems often use real-time operating systems (RTOS) or specialized firmware tailored to the specific application. They may have a minimal or custom user interface, such as a small LCD screen, buttons, or touch panels. Some embedded systems may not have a user interface at all and operate solely based on input from sensors or other connected devices.

4. Connectivity and Networking:
   - PC: Personal computers are designed to be highly connected and offer extensive networking capabilities. They typically have built-in Ethernet ports, Wi-Fi adapters, and support for various connectivity standards like USB, Bluetooth, and HDMI. PCs are commonly used for tasks that require internet access, online communication, file sharing, and networked gaming.
   - Embedded System: Embedded systems can vary in terms of connectivity options depending on their intended application. While many embedded systems do support networking and connectivity, they often have specific and limited networking capabilities tailored to their function. For example, an embedded system in a smart home device may have Wi-Fi or Zigbee connectivity to communicate with other devices within the home network, while an embedded system in an industrial machine may use industrial communication protocols like Modbus or CAN bus for inter-device communication.


3. Με 1000$ σύστημα που θα τεθεί σε τροχιά γύρω από τον Αρη και θα συλλέγει ηχητικά κύματα τα οποία και θα στέλνει πίσω στη γη. 
	α. Επεξ. 16 Πυρήνων για παράλληλη επεξ. και μονάδα ΑΙ (600$)
	β. Επεξ. 02 Πυρήνων (200$)
	γ. Αισθητήρα Ήχου με πολλαπλούς αισθ. για αξιοπιστία (300$)
	δ. Έναν Αισθητήρα (200$)
	ε. Υποσύστημα Ασ. Μετ. με πολλαπλούς πομπούς για αξιοπιστία (300$)
	στ.Μονό Υποσύστημα Ασ. Μετ. (200$)
