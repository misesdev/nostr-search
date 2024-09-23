'use client'

import { Event } from "@/services/relaysPool/types"

type lastNotesProps = {
    events: Event[]
}

const LastNotes = ({ events }: lastNotesProps) => {

    return (
        <>
            <div className="snap-proximity snap-x">
                { events && 
                    events.map((event, key) => {
                        return (
                            <div key={key} className="snap-center">
                                {event.content}
                            </div>
                        )  
                    }) 
                }
            </div>
        </>
    )
}

export default LastNotes

