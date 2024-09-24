import { Event, Filter } from "./types"
import { distinctEvent } from "@/utils/utils";

export class RelayPool {

    private relays: string[];
    public websockets: WebSocket[];
    public timeout: number = 1500;
    public connecting: boolean = false;
    private subscription: string = "3da9794398579582309458d6f1498";

    constructor(relays: string[], subscription: string = '') {
        if(relays.length < 1)
            throw Error("expected relays");

        this.relays = relays; 
        this.websockets = [];

        if(subscription) 
            this.subscription = subscription
    }

    private async connectRelay(relay: string) : Promise<WebSocket | null> 
    {
        return new Promise((resolve, reject) => {
            var timeout: any;

            let websock = new WebSocket(relay);
            websock.onopen = () => {
                console.log("connected to relay", relay)
                resolve(websock);
            }
            websock.onclose = () => {
                console.log(`closed connection: ${relay}`)
                reject(null)
            }
            websock.onerror = () => {
                console.log(`not connetd: ${relay}`)
                reject(null)
            }

            timeout = setTimeout(() => {
                // if (websock.readyState !== WebSocket.OPEN) {
                //     console.error(`connection timeout: ${relay}`);
                //     //websock.close()
                //     reject(null)
                // }
                resolve(null)
            }, this.timeout)
        });
    }

    public async connect() 
    {
        this.connecting = true

        let websockets = this.relays.map(relay => this.connectRelay(relay))

        const sockets = await Promise.all(websockets)

        this.websockets = sockets.filter(socket => socket != null) as WebSocket[]

        this.connecting = false
    }

    private async fetchEventRelay(websocket: WebSocket, filter: Filter): Promise<Event[]> 
    {
        return new Promise((resolve) => {
            let timeout: any;
            let events: Event[] = []
            // send the message
            websocket.send(`[
                "REQ", 
                "${this.subscription}", 
                ${JSON.stringify(filter)}
            ]`);
            
            // receive the event and return
            const handleMessage = (event: any) => {
                try 
                {
                    let data = JSON.parse(event.data);            
                    
                    if (Array.isArray(data) && data.length > 0) {
                        if(data[0] == "EVENT") {
                            let event: Event = data[2];
                            console.log("listened events", event)
                            events.push(event);
                        }

                        if(data[0] == "EOSE") {
                            websocket.removeEventListener("message", handleMessage)
                            clearTimeout(timeout)
                            resolve(events)
                        }
                    }
                } 
                catch(error) {
                    websocket.removeEventListener("message", handleMessage)
                    clearTimeout(timeout)
                    console.log(error)
                    resolve(events)
                }
            }

            websocket.onmessage = handleMessage

            // remove the listener in timeout
            timeout = setTimeout(() => { 
                websocket.removeEventListener("message", handleMessage)
                console.log(`timeout: ${websocket.url}`)
                resolve(events);
            }, this.timeout);
        });
    }

    public async fechEvents(filter: Filter): Promise<Event[]> 
    {
        console.log("fetch events")
        let eventPromises = this.websockets.map(async (websocket) => { 
            return this.fetchEventRelay(websocket, filter).catch((error:string) => {
                console.log(error)
                return [];
            })
        })

        let allEvents = await Promise.all(eventPromises)

        let events = allEvents.flat()

        return distinctEvent(events)
    }

    public async fechUser(pubkey: string): Promise<Event | null> 
    {
        let events = await this.fechEvents({
            kinds: [0],
            authors: [pubkey],
            limit: 1
        });

        if(events.length > 0) return events[0];

        return null;
    }

    public async close() 
    {
        this.websockets.forEach(ws => ws?.close())
    }
}
