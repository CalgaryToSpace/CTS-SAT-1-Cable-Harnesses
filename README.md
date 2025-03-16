# CTS-SAT-1-Cable-Harnesses

## Summary

Diagrams of each cable harness to document how they must be constructed. Created using wireviz.

Online website for Wireviz: https://kroki.io/

## Wireviz Setup

1. Wireviz runs on Python and as such Python must be installed and added to your PATH variables (https://phoenixnap.com/kb/add-python-to-path\)

2. Note that having the wrong Python version or installation running (i.e. one that hasn't been added to your PATH variables) will prevent you from running wireviz in the terminal. 

    For example, you may have added Python 3.11 to your PATH variables, but when running ```python --version``` in     the terminal, find that you are actually running Python 3.13. Switching between versions can be confusing so      an easy solution is to just have one Python version installed. You can also just add each of your Python          installations to your PATH.
    
3. Install Graphviz: ```pip install graphviz```

4. Install WireViz: ```pip install wireviz```

5. Restart your terminal / command prompt and test: ```wireviz --version```

## Repository Structure

```
CTS-SAT-1-Cable-Harnesses
├─ .gitignore
├─ LICENSE
├─ README.md
├─ connectors.bom.tsv
├─ connectors.html
├─ connectors.png
├─ connectors.svg
├─ connectors.yaml
└─ todo.txt
```

The ```connectors.yaml``` file contains all of the code for this repository. The diagrams are outputted in ```connectors.png```, ```connectors.html```, and ```connectors.svg``` (any of these can be used for viewing the diagrams). 

Running ```wireviz connectors.yaml``` in the terminal will update the output files after making changes to ```connectors.yaml```. Make sure to navigate to this repository's folder in your terminal first!

## File Structure

**```connectors.yaml``` has three different sections:**

1. In the **connectors** section, we define each connector. Currently, each connector is labelled with the connector type (e.g. Picoblade) and either the pin labels or the pin count. Ideally, these should be updated so that each connector has all of the pins labelled. Labelling the pins automatically also displays the pin count in the harness diagrams.

    **Example: OBC - J3 connector**
    
    ```yaml    
    connectors:
      OBC - J3:
      type: Picoblade
      pinlabels: [NC, NC, MOSI_USART3_TX, MOSI_USART3_RX, NC, NC, GPS_PPS, NC]
    ```

2. Next is the **cables** section where is each cable is defined. Note that the actual cable names do not matter, though ideally they should follow the same names as in the cable harnesses spreadsheet. For cables, the wire count, length, and color (for visiblity) are currently specified.

    **Example: Harness 1 cable**
    
    ```yaml
    cables:
      Harness 1 - MPI 12V Power:
        wirecount: 4
        length: 200 mm
        colors: [VT, BK, OG, YE]
    ```

3. Finally, the **connections** section is where we specify two connectors and the cable that connects them together. The first line has the first connector, the second line has the cable, and the third line has the second connector. The connector and cable names must match those specified in the connectors and cables sections.

    **Example: Harness 1 connection**
    
    ```
    connections:
      -
        - OBC - J4: [1-4]
        - Harness 1 - MPI 12V Power: [1-4]
        - EPS - J10 VD3_OBC[0]: [1-4]
    ```
    
    Note that we specify which pins are being used to make the connection. This can be done by providing a range      as in the above example or listing specific pins, such as in the harness 7 connection.
    
    ```
    - OBC - J3: [3,4,7]
    - Harness 7 - GPS Connector: [3,4,7]
    - GPS: [3,4,7]
    ```

## Further WireViz Syntax

We can specify many other attributes for the connectors, cables, and connections. A full breakdown of the WireViz syntax can be found at: https://github.com/wireviz/WireViz/blob/master/docs/syntax.md