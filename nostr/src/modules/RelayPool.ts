import { WebSocket } from "ws"
import { Event, Filter } from "./types"

export class RelayPool {

    private relays: string[];
    public websockets: WebSocket[] = [];
    public result: Event[] = [];
    private subscription: string = "3da979448d9ba263864c4d6f14984c42";

    constructor(relays: string[]) {
        if(relays.length < 1)
            throw Error("expected relays");

        this.relays = relays; 
    }

    private async connectRelay(relay: string) : Promise<WebSocket> {
        return new Promise((resolve, reject) => {
            let websock = new WebSocket(relay);
            websock.on("open", () => resolve(websock));
            websock.on("close", () => reject(`not connetd: ${relay}`))
            websock.on("error", () => reject(`not connetd: ${relay}`))
        });
    }

    public async connect() {
        for(let i = 0; i < this.relays.length; i++) {
            let socket = await this.connectRelay(this.relays[i])
                .catch(error => console.log(error))
            if(socket) {
                this.websockets.push(socket);
            }
        } 
    }

    private async fetchEventRelay(socket: WebSocket, filter: Filter) {
        return new Promise((resolve, reject) => {
            socket.send(`["REQ", 
                "${this.subscription}", 
                ${JSON.stringify(filter)}]`);

            socket.on("message", (message) => {
                let data = JSON.parse(message.toString());
                if(data[0] == "EVENT") {
                    let event: Event = data[2];
                    if(this.result.filter(e => e.id == event.id).length <= 0) {
                        this.result.push(event);
                    }
                }
                resolve(true)
            })
        });
    }

    public async fechEvent(filter: Filter): Promise<Event[]> {
       
        for(let i = 0; i < this.websockets.length; i++) {
            await this.fetchEventRelay(this.websockets[i], filter)
        } 

        return this.result;
    }
}
