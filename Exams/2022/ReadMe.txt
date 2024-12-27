1. (8 μονάδες)
	α.Διαφορές Polling με Interrupts 
Απάντηση :
	Here are the key differences between polling and interrupts:

1. Control Flow:
   - Polling: In polling, the control flow is determined by the CPU. The CPU actively checks the device's status at regular intervals to determine if there are any events or data available. It continuously loops through the polling routine until the desired condition is met or data is received.
   - Interrupts: With interrupts, the control flow is determined by the device itself. When an event or data is ready, the device sends an interrupt signal to the CPU, which interrupts the current execution and transfers control to the interrupt handler. The CPU then executes the interrupt handler routine to process the event or data.

2. CPU Utilization:
   - Polling: Polling can consume significant CPU resources since the CPU is actively engaged in checking the device's status, even when no events or data are available. This can lead to higher CPU utilization, potentially impacting the performance of other tasks.
   - Interrupts: Interrupts reduce CPU utilization as the CPU can focus on other tasks until an interrupt occurs. The CPU is not continuously involved in checking the device's status, allowing it to perform other operations. This improves overall system efficiency and responsiveness.

3. Responsiveness:
   - Polling: Polling may introduce latency in detecting events or data since the CPU needs to iterate through the polling routine to identify any changes. The delay between event occurrence and detection depends on the polling interval.
   - Interrupts: Interrupts offer immediate responsiveness as the device directly signals the CPU when an event occurs. The CPU can promptly handle the interrupt, minimizing any potential delays. This results in faster response times for time-sensitive operations.

4. Multitasking:
   - Polling: Polling can make multitasking challenging since the CPU needs to continuously check the status of one or more devices. The CPU must allocate sufficient time for each device, potentially affecting the performance of other tasks.
   - Interrupts: Interrupts facilitate multitasking as the CPU can handle interrupts from different devices simultaneously. By prioritizing interrupts and their corresponding interrupt handlers, the CPU can efficiently manage multiple devices and events, allowing for effective multitasking.

In summary, polling involves active CPU involvement and control flow, leading to higher CPU utilization and potential latency. Interrupts provide better CPU utilization, immediate responsiveness, and support for multitasking by allowing the device to signal the CPU when events occur. The choice between polling and interrupts depends on factors such as system requirements, device characteristics, and the desired balance between CPU utilization and responsiveness.

	β. Πλεονεκτήματα και Μειονεκτήματα 
Απάντηση :
	Certainly! Here are the pros and cons of using polling and interrupts for communication:

Polling:
Pros:
1. Simplicity: Polling is relatively straightforward to implement since it involves continuously checking the status of a device.
2. Control: With polling, the CPU has direct control over when to check the device's status, allowing for fine-grained control of timing and synchronization.
3. Compatibility: Polling can be used in situations where interrupts are not supported or feasible, such as when communicating with certain legacy or simple devices.

Cons:
1. CPU Utilization: Polling can result in higher CPU utilization since the CPU must continually check the device's status, even when no data or events are available.
2. Latency: There can be increased latency between the occurrence of an event and the CPU detecting it, as the event might not be immediately recognized during the polling interval.
3. Inefficiency: Polling can waste CPU cycles by constantly checking the device's status, even if there is no data or events to process.

Interrupts:
Pros:
1. Efficiency: Interrupt-driven systems can reduce CPU utilization by allowing the CPU to perform other tasks until an interrupt occurs, rather than continuously checking device status.
2. Responsiveness: Interrupts offer faster response times since the CPU can promptly handle events as they occur, minimizing any potential delays.
3. Multitasking: Interrupts enable multitasking, allowing the CPU to handle multiple devices or events simultaneously by prioritizing and responding to interrupts accordingly.

Cons:
1. Complexity: Interrupt-driven systems require more complex hardware and software design, as they involve interrupt controllers, interrupt handlers, and synchronization mechanisms.
2. Overhead: Handling interrupts incurs some overhead, such as saving and restoring CPU states, context switching, and executing interrupt service routines (ISRs), which can introduce some latency.
3. Priority and Timing: Interrupts need to be properly prioritized to ensure critical events receive timely attention. Handling interrupts in a timely and efficient manner requires careful consideration of interrupt priorities and proper design.

In summary, polling offers simplicity and direct control but can result in higher CPU utilization and increased latency. Interrupts provide efficiency, responsiveness, and multitasking capabilities but require more complex design and introduce overhead. The choice between polling and interrupts depends on the specific requirements of the system, the nature of the devices being communicated with, and the desired trade-offs between CPU utilization, responsiveness, and system complexity.


2. Interrupts or Polling for the Communication with the HardDrive ? (4 μονάδες)

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

3. (8 μονάδες)
   Επεξ. 1W το δευτερολεπτο (νοείται αυτό ?) και μπορεί να εκτελέσει 100M εντολές το δευτερόλεπτο . 
   Επεξ. 0.1W το δευτερολεπτο (νοείται αυτό ?) και μπορεί να εκτελέσει 1M εντολές το δευτερόλεπτο .    
   Θες να σχεδιάσεις ενσωμ. σύστημα στην Ανταρκτική και θα ελέγχει αν θα έχει φως η σκοτάδι με συχνότητα 1Hz και ανάλογα θα στέλνει σήμα μέσω ασύρματου δικτύου την πληροφορία αυτή.
   Τι θα χρησιμοποιούσατε και γιατί ?




